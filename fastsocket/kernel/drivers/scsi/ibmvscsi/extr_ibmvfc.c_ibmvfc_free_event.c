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
struct ibmvfc_event_pool {int dummy; } ;
struct ibmvfc_host {int /*<<< orphan*/  free; struct ibmvfc_event_pool pool; } ;
struct ibmvfc_event {int /*<<< orphan*/  queue; int /*<<< orphan*/  free; struct ibmvfc_host* vhost; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibmvfc_valid_event (struct ibmvfc_event_pool*,struct ibmvfc_event*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmvfc_free_event(struct ibmvfc_event *evt)
{
	struct ibmvfc_host *vhost = evt->vhost;
	struct ibmvfc_event_pool *pool = &vhost->pool;

	BUG_ON(!ibmvfc_valid_event(pool, evt));
	BUG_ON(atomic_inc_return(&evt->free) != 1);
	list_add_tail(&evt->queue, &vhost->free);
}