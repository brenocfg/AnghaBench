#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
struct ehca_mr {TYPE_1__ ipz_mr_handle; } ;

/* Variables and functions */
 int EHCA_PAGESIZE ; 
 int H_PARAMETER ; 
 scalar_t__ abs_to_virt (int const) ; 
 int ehca_debug_level ; 
 int /*<<< orphan*/  ehca_gen_dbg (char*,void*,...) ; 
 int /*<<< orphan*/  ehca_gen_err (char*,int /*<<< orphan*/ ,struct ehca_mr const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int const,int const) ; 
 int hipz_h_register_rpage (struct ipz_adapter_handle const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int const,int const) ; 
 scalar_t__ unlikely (int) ; 

u64 hipz_h_register_rpage_mr(const struct ipz_adapter_handle adapter_handle,
			     const struct ehca_mr *mr,
			     const u8 pagesize,
			     const u8 queue_type,
			     const u64 logical_address_of_page,
			     const u64 count)
{
	u64 ret;

	if (unlikely(ehca_debug_level >= 3)) {
		if (count > 1) {
			u64 *kpage;
			int i;
			kpage = (u64 *)abs_to_virt(logical_address_of_page);
			for (i = 0; i < count; i++)
				ehca_gen_dbg("kpage[%d]=%p",
					     i, (void *)kpage[i]);
		} else
			ehca_gen_dbg("kpage=%p",
				     (void *)logical_address_of_page);
	}

	if ((count > 1) && (logical_address_of_page & (EHCA_PAGESIZE-1))) {
		ehca_gen_err("logical_address_of_page not on a 4k boundary "
			     "adapter_handle=%llx mr=%p mr_handle=%llx "
			     "pagesize=%x queue_type=%x "
			     "logical_address_of_page=%llx count=%llx",
			     adapter_handle.handle, mr,
			     mr->ipz_mr_handle.handle, pagesize, queue_type,
			     logical_address_of_page, count);
		ret = H_PARAMETER;
	} else
		ret = hipz_h_register_rpage(adapter_handle, pagesize,
					    queue_type,
					    mr->ipz_mr_handle.handle,
					    logical_address_of_page, count);
	return ret;
}