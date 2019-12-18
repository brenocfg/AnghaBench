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
struct target_notify {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct target_notify*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct target_notify*) ; 
 int /*<<< orphan*/  target_notify ; 
 int /*<<< orphan*/  target_notifylist ; 
 int /*<<< orphan*/  tn ; 

int
target_delete_notify(struct target_notify *notify)
{
	SLIST_REMOVE(&target_notifylist, notify, target_notify, tn);
	free(notify);

	return (0);
}