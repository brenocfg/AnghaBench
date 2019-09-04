#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  hibernate_page_list_t ;
struct TYPE_3__ {scalar_t__ efiRuntimeServicesPageCount; scalar_t__ efiRuntimeServicesPageStart; } ;
typedef  TYPE_1__ boot_args ;
struct TYPE_4__ {scalar_t__ bootArgs; } ;

/* Variables and functions */
 TYPE_2__ PE_state ; 
 int /*<<< orphan*/  hibernate_set_page_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kIOHibernatePageStateFree ; 

void
hibernate_page_list_set_volatile( hibernate_page_list_t * page_list,
				  hibernate_page_list_t * page_list_wired,
				  uint32_t * pagesOut)
{
    boot_args * args = (boot_args *) PE_state.bootArgs;

    if (args->efiRuntimeServicesPageStart)
    {
	hibernate_set_page_state(page_list, page_list_wired, 
		    args->efiRuntimeServicesPageStart, args->efiRuntimeServicesPageCount, 
		    kIOHibernatePageStateFree);
	*pagesOut -= args->efiRuntimeServicesPageCount;
    }
}