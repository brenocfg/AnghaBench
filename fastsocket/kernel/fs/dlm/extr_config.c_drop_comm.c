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
struct dlm_comm {size_t addr_count; int /*<<< orphan*/ * addr; int /*<<< orphan*/  nodeid; } ;
struct config_item {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 struct dlm_comm* config_item_to_comm (struct config_item*) ; 
 int /*<<< orphan*/  dlm_lowcomms_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct dlm_comm* local_comm ; 

__attribute__((used)) static void drop_comm(struct config_group *g, struct config_item *i)
{
	struct dlm_comm *cm = config_item_to_comm(i);
	if (local_comm == cm)
		local_comm = NULL;
	dlm_lowcomms_close(cm->nodeid);
	while (cm->addr_count--)
		kfree(cm->addr[cm->addr_count]);
	config_item_put(i);
}