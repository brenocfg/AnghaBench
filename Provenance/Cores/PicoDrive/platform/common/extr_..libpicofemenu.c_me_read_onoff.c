#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mask; scalar_t__ var; } ;
typedef  TYPE_1__ menu_entry ;

/* Variables and functions */

__attribute__((used)) static unsigned int me_read_onoff(const menu_entry *ent)
{
	// guess var size based on mask to avoid reading too much
	if (ent->mask & 0xffff0000)
		return *(unsigned int *)ent->var & ent->mask;
	else if (ent->mask & 0xff00)
		return *(unsigned short *)ent->var & ent->mask;
	else
		return *(unsigned char *)ent->var & ent->mask;
}