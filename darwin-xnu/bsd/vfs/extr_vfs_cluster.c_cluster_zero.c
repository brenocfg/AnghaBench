#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  upl_t ;
typedef  int /*<<< orphan*/  upl_page_info_t ;
typedef  int upl_offset_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  TYPE_1__* buf_t ;
typedef  int addr64_t ;
struct TYPE_4__ {scalar_t__ b_datap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FSRW ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int FSDBG_CODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero_phys (int,int) ; 
 int /*<<< orphan*/  bzero_phys_nc (int,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/ * ubc_upl_pageinfo (int /*<<< orphan*/ ) ; 
 scalar_t__ upl_device_page (int /*<<< orphan*/ *) ; 
 scalar_t__ upl_phys_page (int /*<<< orphan*/ *,int) ; 

void
cluster_zero(upl_t upl, upl_offset_t upl_offset, int size, buf_t bp)
{

	KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 23)) | DBG_FUNC_START,
		     upl_offset, size, bp, 0, 0);

	if (bp == NULL || bp->b_datap == 0) {
	        upl_page_info_t *pl;
	        addr64_t	zero_addr;

	        pl = ubc_upl_pageinfo(upl);

		if (upl_device_page(pl) == TRUE) {
		        zero_addr = ((addr64_t)upl_phys_page(pl, 0) << PAGE_SHIFT) + upl_offset;

			bzero_phys_nc(zero_addr, size);
		} else {
		        while (size) {
			        int	page_offset;
				int	page_index;
				int	zero_cnt;

				page_index  = upl_offset / PAGE_SIZE;
				page_offset = upl_offset & PAGE_MASK;

				zero_addr = ((addr64_t)upl_phys_page(pl, page_index) << PAGE_SHIFT) + page_offset;
				zero_cnt  = min(PAGE_SIZE - page_offset, size);

				bzero_phys(zero_addr, zero_cnt);

				size       -= zero_cnt;
				upl_offset += zero_cnt;
			}
		}
	} else
		bzero((caddr_t)((vm_offset_t)bp->b_datap + upl_offset), size);

	KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 23)) | DBG_FUNC_END,
		     upl_offset, size, 0, 0, 0);
}