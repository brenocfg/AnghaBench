#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mptsas_phyinfo {int dummy; } ;
struct mptsas_devinfo {int flags; int /*<<< orphan*/  sas_address; } ;
typedef  TYPE_4__* pRaidVolumePage0_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_20__ {TYPE_7__* hdr; } ;
struct TYPE_26__ {int pageAddr; int PageLength; int /*<<< orphan*/  action; int /*<<< orphan*/  physAddr; int /*<<< orphan*/  timeout; TYPE_1__ cfghdr; int /*<<< orphan*/  PageType; } ;
struct TYPE_25__ {int /*<<< orphan*/  pcidev; } ;
struct TYPE_24__ {int PhysDiskBus; scalar_t__ PhysDiskID; } ;
struct TYPE_21__ {int Flags; } ;
struct TYPE_23__ {int NumPhysDisks; TYPE_3__* PhysDisk; TYPE_2__ VolumeStatus; } ;
struct TYPE_22__ {int /*<<< orphan*/  PhysDiskNum; } ;
typedef  TYPE_5__ RaidPhysDiskPage0_t ;
typedef  TYPE_6__ MPT_ADAPTER ;
typedef  TYPE_7__ ConfigPageHeader_t ;
typedef  TYPE_7__ CONFIGPARMS ;

/* Variables and functions */
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_HEADER ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_READ_CURRENT ; 
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_RAID_VOLUME ; 
 int MPI_RAIDVOL0_STATUS_FLAG_VOLUME_INACTIVE ; 
 int MPI_SAS_DEVICE0_FLAGS_DEVICE_MAPPED ; 
 int MPI_SAS_DEVICE0_FLAGS_DEVICE_PRESENT ; 
 int MPI_SAS_DEVICE_PGAD_FORM_BUS_TARGET_ID ; 
 int MPI_SAS_DEVICE_PGAD_FORM_SHIFT ; 
 int /*<<< orphan*/  SAS_CONFIG_PAGE_TIMEOUT ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mpt_config (TYPE_6__*,TYPE_7__*) ; 
 scalar_t__ mpt_raid_phys_disk_pg0 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  mptsas_add_end_device (TYPE_6__*,struct mptsas_phyinfo*) ; 
 struct mptsas_phyinfo* mptsas_find_phyinfo_by_sas_address (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mptsas_sas_device_pg0 (TYPE_6__*,struct mptsas_devinfo*,int,scalar_t__) ; 
 TYPE_4__* pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mptsas_adding_inactive_raid_components(MPT_ADAPTER *ioc, u8 channel, u8 id)
{
	CONFIGPARMS			cfg;
	ConfigPageHeader_t		hdr;
	dma_addr_t			dma_handle;
	pRaidVolumePage0_t		buffer = NULL;
	RaidPhysDiskPage0_t 		phys_disk;
	int				i;
	struct mptsas_phyinfo	*phy_info;
	struct mptsas_devinfo		sas_device;

	memset(&cfg, 0 , sizeof(CONFIGPARMS));
	memset(&hdr, 0 , sizeof(ConfigPageHeader_t));
	hdr.PageType = MPI_CONFIG_PAGETYPE_RAID_VOLUME;
	cfg.pageAddr = (channel << 8) + id;
	cfg.cfghdr.hdr = &hdr;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.timeout = SAS_CONFIG_PAGE_TIMEOUT;

	if (mpt_config(ioc, &cfg) != 0)
		goto out;

	if (!hdr.PageLength)
		goto out;

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.PageLength * 4,
	    &dma_handle);

	if (!buffer)
		goto out;

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	if (mpt_config(ioc, &cfg) != 0)
		goto out;

	if (!(buffer->VolumeStatus.Flags &
	    MPI_RAIDVOL0_STATUS_FLAG_VOLUME_INACTIVE))
		goto out;

	if (!buffer->NumPhysDisks)
		goto out;

	for (i = 0; i < buffer->NumPhysDisks; i++) {

		if (mpt_raid_phys_disk_pg0(ioc,
		    buffer->PhysDisk[i].PhysDiskNum, &phys_disk) != 0)
			continue;

		if (mptsas_sas_device_pg0(ioc, &sas_device,
		    (MPI_SAS_DEVICE_PGAD_FORM_BUS_TARGET_ID <<
		     MPI_SAS_DEVICE_PGAD_FORM_SHIFT),
			(phys_disk.PhysDiskBus << 8) +
			phys_disk.PhysDiskID))
			continue;

		/* If there is no FW B_T mapping for this device then continue
		 * */
		if (!(sas_device.flags & MPI_SAS_DEVICE0_FLAGS_DEVICE_PRESENT)
			|| !(sas_device.flags &
			MPI_SAS_DEVICE0_FLAGS_DEVICE_MAPPED))
			continue;


		phy_info = mptsas_find_phyinfo_by_sas_address(ioc,
		    sas_device.sas_address);
		mptsas_add_end_device(ioc, phy_info);
	}

 out:
	if (buffer)
		pci_free_consistent(ioc->pcidev, hdr.PageLength * 4, buffer,
		    dma_handle);
}