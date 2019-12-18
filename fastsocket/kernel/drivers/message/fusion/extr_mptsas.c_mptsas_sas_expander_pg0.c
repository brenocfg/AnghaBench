#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct mptsas_portinfo {int num_phys; TYPE_12__* phy_info; } ;
struct mptsas_phyinfo {int dummy; } ;
typedef  int dma_addr_t ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_14__ {TYPE_5__* ehdr; } ;
struct TYPE_19__ {int physAddr; int /*<<< orphan*/  action; int /*<<< orphan*/  timeout; scalar_t__ dir; scalar_t__ pageAddr; TYPE_1__ cfghdr; } ;
struct TYPE_18__ {int ExtPageLength; int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  PageType; scalar_t__ Reserved2; scalar_t__ Reserved1; scalar_t__ PageNumber; int /*<<< orphan*/  PageVersion; } ;
struct TYPE_17__ {int /*<<< orphan*/  pcidev; } ;
struct TYPE_16__ {int NumPhys; int /*<<< orphan*/  ParentDevHandle; int /*<<< orphan*/  DevHandle; int /*<<< orphan*/  SASAddress; } ;
struct TYPE_15__ {void* handle_parent; int /*<<< orphan*/  sas_address; } ;
struct TYPE_13__ {TYPE_2__ identify; void* handle; struct mptsas_portinfo* portinfo; } ;
typedef  TYPE_3__ SasExpanderPage0_t ;
typedef  TYPE_4__ MPT_ADAPTER ;
typedef  TYPE_5__ ConfigExtendedPageHeader_t ;
typedef  TYPE_6__ CONFIGPARMS ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_HEADER ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_READ_CURRENT ; 
 int /*<<< orphan*/  MPI_CONFIG_EXTPAGETYPE_SAS_EXPANDER ; 
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_EXTENDED ; 
 int MPI_IOCSTATUS_CONFIG_INVALID_PAGE ; 
 int /*<<< orphan*/  MPI_SASEXPANDER0_PAGEVERSION ; 
 int /*<<< orphan*/  SAS_CONFIG_PAGE_TIMEOUT ; 
 TYPE_12__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct mptsas_portinfo*,int /*<<< orphan*/ ,int) ; 
 int mpt_config (TYPE_4__*,TYPE_6__*) ; 
 TYPE_3__* pci_alloc_consistent (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,TYPE_3__*,int) ; 

__attribute__((used)) static int
mptsas_sas_expander_pg0(MPT_ADAPTER *ioc, struct mptsas_portinfo *port_info,
		u32 form, u32 form_specific)
{
	ConfigExtendedPageHeader_t hdr;
	CONFIGPARMS cfg;
	SasExpanderPage0_t *buffer;
	dma_addr_t dma_handle;
	int i, error;
	__le64 sas_address;

	memset(port_info, 0, sizeof(struct mptsas_portinfo));
	hdr.PageVersion = MPI_SASEXPANDER0_PAGEVERSION;
	hdr.ExtPageLength = 0;
	hdr.PageNumber = 0;
	hdr.Reserved1 = 0;
	hdr.Reserved2 = 0;
	hdr.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	hdr.ExtPageType = MPI_CONFIG_EXTPAGETYPE_SAS_EXPANDER;

	cfg.cfghdr.ehdr = &hdr;
	cfg.physAddr = -1;
	cfg.pageAddr = form + form_specific;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;	/* read */
	cfg.timeout = SAS_CONFIG_PAGE_TIMEOUT;

	memset(port_info, 0, sizeof(struct mptsas_portinfo));
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
	if (error == MPI_IOCSTATUS_CONFIG_INVALID_PAGE) {
		error = -ENODEV;
		goto out_free_consistent;
	}

	if (error)
		goto out_free_consistent;

	/* save config data */
	port_info->num_phys = (buffer->NumPhys) ? buffer->NumPhys : 1;
	port_info->phy_info = kcalloc(port_info->num_phys,
		sizeof(struct mptsas_phyinfo), GFP_KERNEL);
	if (!port_info->phy_info) {
		error = -ENOMEM;
		goto out_free_consistent;
	}

	memcpy(&sas_address, &buffer->SASAddress, sizeof(__le64));
	for (i = 0; i < port_info->num_phys; i++) {
		port_info->phy_info[i].portinfo = port_info;
		port_info->phy_info[i].handle =
		    le16_to_cpu(buffer->DevHandle);
		port_info->phy_info[i].identify.sas_address =
		    le64_to_cpu(sas_address);
		port_info->phy_info[i].identify.handle_parent =
		    le16_to_cpu(buffer->ParentDevHandle);
	}

 out_free_consistent:
	pci_free_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
			    buffer, dma_handle);
 out:
	return error;
}