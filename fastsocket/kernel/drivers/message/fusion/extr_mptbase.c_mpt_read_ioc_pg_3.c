#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int dma_addr_t ;
struct TYPE_9__ {TYPE_4__* hdr; } ;
struct TYPE_13__ {int physAddr; int /*<<< orphan*/  action; scalar_t__ timeout; scalar_t__ dir; scalar_t__ pageAddr; TYPE_1__ cfghdr; } ;
struct TYPE_12__ {int PageLength; int PageNumber; int /*<<< orphan*/  PageType; scalar_t__ PageVersion; } ;
struct TYPE_10__ {int /*<<< orphan*/ * pIocPg3; } ;
struct TYPE_11__ {int /*<<< orphan*/  pcidev; TYPE_2__ raid_data; } ;
typedef  TYPE_3__ MPT_ADAPTER ;
typedef  int /*<<< orphan*/  IOCPage3_t ;
typedef  TYPE_4__ ConfigPageHeader_t ;
typedef  TYPE_5__ CONFIGPARMS ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_HEADER ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_READ_CURRENT ; 
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_IOC ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mpt_config (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
mpt_read_ioc_pg_3(MPT_ADAPTER *ioc)
{
	IOCPage3_t		*pIoc3;
	u8			*mem;
	CONFIGPARMS		 cfg;
	ConfigPageHeader_t	 header;
	dma_addr_t		 ioc3_dma;
	int			 iocpage3sz = 0;

	/* Free the old page
	 */
	kfree(ioc->raid_data.pIocPg3);
	ioc->raid_data.pIocPg3 = NULL;

	/* There is at least one physical disk.
	 * Read and save IOC Page 3
	 */
	header.PageVersion = 0;
	header.PageLength = 0;
	header.PageNumber = 3;
	header.PageType = MPI_CONFIG_PAGETYPE_IOC;
	cfg.cfghdr.hdr = &header;
	cfg.physAddr = -1;
	cfg.pageAddr = 0;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;
	cfg.timeout = 0;
	if (mpt_config(ioc, &cfg) != 0)
		return 0;

	if (header.PageLength == 0)
		return 0;

	/* Read Header good, alloc memory
	 */
	iocpage3sz = header.PageLength * 4;
	pIoc3 = pci_alloc_consistent(ioc->pcidev, iocpage3sz, &ioc3_dma);
	if (!pIoc3)
		return 0;

	/* Read the Page and save the data
	 * into malloc'd memory.
	 */
	cfg.physAddr = ioc3_dma;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;
	if (mpt_config(ioc, &cfg) == 0) {
		mem = kmalloc(iocpage3sz, GFP_KERNEL);
		if (mem) {
			memcpy(mem, (u8 *)pIoc3, iocpage3sz);
			ioc->raid_data.pIocPg3 = (IOCPage3_t *) mem;
		}
	}

	pci_free_consistent(ioc->pcidev, iocpage3sz, pIoc3, ioc3_dma);

	return 0;
}