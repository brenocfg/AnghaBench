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
struct ip_vs_service {TYPE_1__* scheduler; int /*<<< orphan*/  num_dests; } ;
struct ip_vs_dest {int /*<<< orphan*/  n_list; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_service ) (struct ip_vs_service*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VS_DEST_F_AVAILABLE ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ip_vs_service*) ; 

__attribute__((used)) static void __ip_vs_unlink_dest(struct ip_vs_service *svc,
				struct ip_vs_dest *dest,
				int svcupd)
{
	dest->flags &= ~IP_VS_DEST_F_AVAILABLE;

	/*
	 *  Remove it from the d-linked destination list.
	 */
	list_del(&dest->n_list);
	svc->num_dests--;

	/*
	 *  Call the update_service function of its scheduler
	 */
	if (svcupd && svc->scheduler->update_service)
			svc->scheduler->update_service(svc);
}