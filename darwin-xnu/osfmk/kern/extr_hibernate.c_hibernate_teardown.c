#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {int /*<<< orphan*/  list_size; } ;
typedef  TYPE_1__ hibernate_page_list_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ TRUE ; 
 scalar_t__ VM_CONFIG_COMPRESSOR_IS_PRESENT ; 
 int /*<<< orphan*/  hibernate_free_gobble_pages () ; 
 int /*<<< orphan*/  kfree (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ need_to_unlock_decompressor ; 
 int /*<<< orphan*/  vm_compressor_delay_trim () ; 
 int /*<<< orphan*/  vm_decompressor_unlock () ; 

kern_return_t 
hibernate_teardown(hibernate_page_list_t * page_list,
                    hibernate_page_list_t * page_list_wired,
		    hibernate_page_list_t * page_list_pal)
{
    hibernate_free_gobble_pages();

    if (page_list)
        kfree(page_list, page_list->list_size);
    if (page_list_wired)
        kfree(page_list_wired, page_list_wired->list_size);
    if (page_list_pal)
        kfree(page_list_pal, page_list_pal->list_size);

    if (VM_CONFIG_COMPRESSOR_IS_PRESENT) {
	    if (need_to_unlock_decompressor == TRUE) {
		    need_to_unlock_decompressor = FALSE;
		    vm_decompressor_unlock();
	    }
	    vm_compressor_delay_trim();
    }
    return (KERN_SUCCESS);
}