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
struct dlm_lock_resource {int /*<<< orphan*/  blocked; int /*<<< orphan*/  converting; int /*<<< orphan*/  granted; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

int __dlm_lockres_has_locks(struct dlm_lock_resource *res)
{
	if (list_empty(&res->granted) &&
	    list_empty(&res->converting) &&
	    list_empty(&res->blocked))
		return 0;
	return 1;
}