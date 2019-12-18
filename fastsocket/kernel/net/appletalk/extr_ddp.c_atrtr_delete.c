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
struct TYPE_2__ {scalar_t__ s_net; scalar_t__ s_node; } ;
struct atalk_route {int flags; struct atalk_route* next; int /*<<< orphan*/  dev; TYPE_1__ target; } ;
struct atalk_addr {scalar_t__ s_net; scalar_t__ s_node; } ;

/* Variables and functions */
 int ENOENT ; 
 int RTF_GATEWAY ; 
 struct atalk_route* atalk_routes ; 
 int /*<<< orphan*/  atalk_routes_lock ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct atalk_route*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atrtr_delete(struct atalk_addr * addr)
{
	struct atalk_route **r = &atalk_routes;
	int retval = 0;
	struct atalk_route *tmp;

	write_lock_bh(&atalk_routes_lock);
	while ((tmp = *r) != NULL) {
		if (tmp->target.s_net == addr->s_net &&
		    (!(tmp->flags&RTF_GATEWAY) ||
		     tmp->target.s_node == addr->s_node)) {
			*r = tmp->next;
			dev_put(tmp->dev);
			kfree(tmp);
			goto out;
		}
		r = &tmp->next;
	}
	retval = -ENOENT;
out:
	write_unlock_bh(&atalk_routes_lock);
	return retval;
}