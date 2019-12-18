#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct mptsas_portinfo {int num_phys; TYPE_13__* phy_info; } ;
struct mptsas_phyinfo {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_16__ {TYPE_4__* ehdr; } ;
struct TYPE_20__ {int physAddr; int /*<<< orphan*/  action; int /*<<< orphan*/  timeout; scalar_t__ dir; scalar_t__ pageAddr; TYPE_1__ cfghdr; } ;
struct TYPE_19__ {int ExtPageLength; int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  PageType; scalar_t__ Reserved2; scalar_t__ Reserved1; scalar_t__ PageNumber; int /*<<< orphan*/  PageVersion; } ;
struct TYPE_18__ {int /*<<< orphan*/  pcidev; void* nvdata_version_default; void* nvdata_version_persistent; } ;
struct TYPE_17__ {int NumPhys; TYPE_10__* PhyData; int /*<<< orphan*/  NvdataVersionDefault; int /*<<< orphan*/  NvdataVersionPersistent; } ;
struct TYPE_15__ {int phy_id; void* handle; struct mptsas_portinfo* portinfo; int /*<<< orphan*/  negotiated_link_rate; int /*<<< orphan*/  port_id; } ;
struct TYPE_14__ {int /*<<< orphan*/  ControllerDevHandle; int /*<<< orphan*/  NegotiatedLinkRate; int /*<<< orphan*/  Port; } ;
typedef  TYPE_2__ SasIOUnitPage0_t ;
typedef  TYPE_3__ MPT_ADAPTER ;
typedef  TYPE_4__ ConfigExtendedPageHeader_t ;
typedef  TYPE_5__ CONFIGPARMS ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_HEADER ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_READ_CURRENT ; 
 int /*<<< orphan*/  MPI_CONFIG_EXTPAGETYPE_SAS_IO_UNIT ; 
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_EXTENDED ; 
 int /*<<< orphan*/  MPI_SASIOUNITPAGE0_PAGEVERSION ; 
 int /*<<< orphan*/  SAS_CONFIG_PAGE_TIMEOUT ; 
 TYPE_13__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int mpt_config (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  mptsas_print_phy_data (TYPE_3__*,TYPE_10__*) ; 
 TYPE_2__* pci_alloc_consistent (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,TYPE_2__*,int) ; 

__attribute__((used)) static int
mptsas_sas_io_unit_pg0(MPT_ADAPTER *ioc, struct mptsas_portinfo *port_info)
{
	ConfigExtendedPageHeader_t hdr;
	CONFIGPARMS cfg;
	SasIOUnitPage0_t *buffer;
	dma_addr_t dma_handle;
	int error, i;

	hdr.PageVersion = MPI_SASIOUNITPAGE0_PAGEVERSION;
	hdr.ExtPageLength = 0;
	hdr.PageNumber = 0;
	hdr.Reserved1 = 0;
	hdr.Reserved2 = 0;
	hdr.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	hdr.ExtPageType = MPI_CONFIG_EXTPAGETYPE_SAS_IO_UNIT;

	cfg.cfghdr.ehdr = &hdr;
	cfg.physAddr = -1;
	cfg.pageAddr = 0;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;	/* read */
	cfg.timeout = SAS_CONFIG_PAGE_TIMEOUT;

	error = mpt_config(ioc, &cfg);
	if (error)
		goto out;
	if (!hdr.ExtPageLength) {
		error = -ENXIO;
		goto out;
	}

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
					    &dma_handle);
	if (!buffer) {
		error = -ENOMEM;
		goto out;
	}

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	error = mpt_config(ioc, &cfg);
	if (error)
		goto out_free_consistent;

	port_info->num_phys = buffer->NumPhys;
	port_info->phy_info = kcalloc(port_info->num_phys,
		sizeof(struct mptsas_phyinfo), GFP_KERNEL);
	if (!port_info->phy_info) {
		error = -ENOMEM;
		goto out_free_consistent;
	}

	ioc->nvdata_version_persistent =
	    le16_to_cpu(buffer->NvdataVersionPersistent);
	ioc->nvdata_version_default =
	    le16_to_cpu(buffer->NvdataVersionDefault);

	for (i = 0; i < port_info->num_phys; i++) {
		mptsas_print_phy_data(ioc, &buffer->PhyData[i]);
		port_info->phy_info[i].phy_id = i;
		port_info->phy_info[i].port_id =
		    buffer->PhyData[i].Port;
		port_info->phy_info[i].negotiated_link_rate =
		    buffer->PhyData[i].NegotiatedLinkRate;
		port_info->phy_info[i].portinfo = port_info;
		port_info->phy_info[i].handle =
		    le16_to_cpu(buffer->PhyData[i].ControllerDevHandle);
	}

 out_free_consistent:
	pci_free_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
			    buffer, dma_handle);
 out:
	return error;
}