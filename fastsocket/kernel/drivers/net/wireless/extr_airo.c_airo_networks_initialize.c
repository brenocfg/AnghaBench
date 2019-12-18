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
struct airo_info {int /*<<< orphan*/  network_free_list; TYPE_1__* networks; int /*<<< orphan*/  network_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int AIRO_MAX_NETWORK_COUNT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void airo_networks_initialize(struct airo_info *ai)
{
	int i;

	INIT_LIST_HEAD(&ai->network_free_list);
	INIT_LIST_HEAD(&ai->network_list);
	for (i = 0; i < AIRO_MAX_NETWORK_COUNT; i++)
		list_add_tail(&ai->networks[i].list,
			      &ai->network_free_list);
}