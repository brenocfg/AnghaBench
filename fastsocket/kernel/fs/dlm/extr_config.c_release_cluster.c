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
struct TYPE_2__ {struct dlm_cluster* default_groups; } ;
struct dlm_cluster {TYPE_1__ group; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 struct dlm_cluster* config_item_to_cluster (struct config_item*) ; 
 int /*<<< orphan*/  kfree (struct dlm_cluster*) ; 

__attribute__((used)) static void release_cluster(struct config_item *i)
{
	struct dlm_cluster *cl = config_item_to_cluster(i);
	kfree(cl->group.default_groups);
	kfree(cl);
}