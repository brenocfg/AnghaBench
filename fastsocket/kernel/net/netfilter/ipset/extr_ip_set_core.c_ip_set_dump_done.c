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
struct netlink_callback {int* args; } ;
typedef  int /*<<< orphan*/  ip_set_id_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__** ip_set_list ; 
 int /*<<< orphan*/  ip_set_put_byindex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ip_set_dump_done(struct netlink_callback *cb)
{
	if (cb->args[2]) {
		pr_debug("release set %s\n", ip_set_list[cb->args[1]]->name);
		ip_set_put_byindex((ip_set_id_t) cb->args[1]);
	}
	return 0;
}