#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_5__ {int blocked; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_1__ publ; scalar_t__ active; } ;

/* Variables and functions */
 size_t MAX_BEARERS ; 
 int /*<<< orphan*/  bearer_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 scalar_t__ media_count ; 
 TYPE_2__* media_list ; 
 TYPE_2__* tipc_bearers ; 

void tipc_bearer_stop(void)
{
	u32 i;

	if (!tipc_bearers)
		return;

	for (i = 0; i < MAX_BEARERS; i++) {
		if (tipc_bearers[i].active)
			tipc_bearers[i].publ.blocked = 1;
	}
	for (i = 0; i < MAX_BEARERS; i++) {
		if (tipc_bearers[i].active)
			bearer_disable(tipc_bearers[i].publ.name);
	}
	kfree(tipc_bearers);
	kfree(media_list);
	tipc_bearers = NULL;
	media_list = NULL;
	media_count = 0;
}