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
struct wan_device {struct wan_device* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 struct wan_device* wanrouter_router_devlist ; 

__attribute__((used)) static struct wan_device *wanrouter_find_device(char *name)
{
	struct wan_device *wandev;

	for (wandev = wanrouter_router_devlist;
	     wandev && strcmp(wandev->name, name);
		wandev = wandev->next);
	return wandev;
}