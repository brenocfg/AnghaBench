#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_13__ {TYPE_5__* ehdr; } ;
struct TYPE_17__ {int ExtPageLength; int /*<<< orphan*/  action; int /*<<< orphan*/  physAddr; TYPE_1__ cfghdr; int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  PageType; int /*<<< orphan*/  PageVersion; } ;
struct TYPE_16__ {int /*<<< orphan*/  pcidev; } ;
struct TYPE_15__ {TYPE_2__* PhyData; } ;
struct TYPE_14__ {int PortFlags; } ;
typedef  TYPE_3__ SasIOUnitPage0_t ;
typedef  TYPE_4__ MPT_ADAPTER ;
typedef  TYPE_5__ ConfigExtendedPageHeader_t ;
typedef  TYPE_5__ CONFIGPARMS ;

/* Variables and functions */
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_HEADER ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_READ_CURRENT ; 
 int /*<<< orphan*/  MPI_CONFIG_EXTPAGETYPE_SAS_IO_UNIT ; 
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_EXTENDED ; 
 int /*<<< orphan*/  MPI_SASIOUNITPAGE0_PAGEVERSION ; 
 int MPI_SAS_IOUNIT0_PORT_FLAGS_DISCOVERY_IN_PROGRESS ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mpt_config (TYPE_4__*,TYPE_5__*) ; 
 TYPE_3__* pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpt_is_discovery_complete(MPT_ADAPTER *ioc)
{
	ConfigExtendedPageHeader_t hdr;
	CONFIGPARMS cfg;
	SasIOUnitPage0_t *buffer;
	dma_addr_t dma_handle;
	int rc = 0;

	memset(&hdr, 0, sizeof(ConfigExtendedPageHeader_t));
	memset(&cfg, 0, sizeof(CONFIGPARMS));
	hdr.PageVersion = MPI_SASIOUNITPAGE0_PAGEVERSION;
	hdr.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	hdr.ExtPageType = MPI_CONFIG_EXTPAGETYPE_SAS_IO_UNIT;
	cfg.cfghdr.ehdr = &hdr;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;

	if ((mpt_config(ioc, &cfg)))
		goto out;
	if (!hdr.ExtPageLength)
		goto out;

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
	    &dma_handle);
	if (!buffer)
		goto out;

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	if ((mpt_config(ioc, &cfg)))
		goto out_free_consistent;

	if (!(buffer->PhyData[0].PortFlags &
	    MPI_SAS_IOUNIT0_PORT_FLAGS_DISCOVERY_IN_PROGRESS))
		rc = 1;

 out_free_consistent:
	pci_free_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
	    buffer, dma_handle);
 out:
	return rc;
}