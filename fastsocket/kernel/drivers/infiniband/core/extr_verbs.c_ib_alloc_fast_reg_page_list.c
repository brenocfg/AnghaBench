#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ib_fast_reg_page_list {int max_page_list_len; struct ib_device* device; } ;
struct ib_device {struct ib_fast_reg_page_list* (* alloc_fast_reg_page_list ) (struct ib_device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 struct ib_fast_reg_page_list* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct ib_fast_reg_page_list*) ; 
 struct ib_fast_reg_page_list* stub1 (struct ib_device*,int) ; 

struct ib_fast_reg_page_list *ib_alloc_fast_reg_page_list(struct ib_device *device,
							  int max_page_list_len)
{
	struct ib_fast_reg_page_list *page_list;

	if (!device->alloc_fast_reg_page_list)
		return ERR_PTR(-ENOSYS);

	page_list = device->alloc_fast_reg_page_list(device, max_page_list_len);

	if (!IS_ERR(page_list)) {
		page_list->device = device;
		page_list->max_page_list_len = max_page_list_len;
	}

	return page_list;
}