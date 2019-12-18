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
struct target_param {scalar_t__ status; int /*<<< orphan*/  socket; } ;
struct target_notify {scalar_t__ status; int /*<<< orphan*/  socket; } ;
struct target_address {scalar_t__ status; int /*<<< orphan*/  socket; } ;

/* Variables and functions */
 scalar_t__ RowStatus_active ; 
 struct target_param* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct target_param*) ; 
 int /*<<< orphan*/  ta ; 
 int /*<<< orphan*/  target_addresslist ; 
 int /*<<< orphan*/  target_notifylist ; 
 int /*<<< orphan*/  target_paramlist ; 
 int /*<<< orphan*/  tn ; 
 int /*<<< orphan*/  tp ; 

void
target_flush_all(void)
{
	struct target_address *addrs;
	struct target_param *param;
	struct target_notify *notify;

	while ((addrs = SLIST_FIRST(&target_addresslist)) != NULL) {
		SLIST_REMOVE_HEAD(&target_addresslist, ta);
		if (addrs->status == RowStatus_active)
			close(addrs->socket);
		free(addrs);
	}
	SLIST_INIT(&target_addresslist);

	while ((param = SLIST_FIRST(&target_paramlist)) != NULL) {
		SLIST_REMOVE_HEAD(&target_paramlist, tp);
		free(param);
	}
	SLIST_INIT(&target_paramlist);

	while ((notify = SLIST_FIRST(&target_notifylist)) != NULL) {
		SLIST_REMOVE_HEAD(&target_notifylist, tn);
		free(notify);
	}
	SLIST_INIT(&target_notifylist);
}