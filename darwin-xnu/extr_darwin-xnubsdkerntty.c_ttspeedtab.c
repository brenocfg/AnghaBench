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
struct speedtab {int sp_speed; int sp_code; } ;

/* Variables and functions */

int
ttspeedtab(int speed, struct speedtab *table)
{
	for ( ; table->sp_speed != -1; table++)
		if (table->sp_speed == speed)
			return (table->sp_code);
	return (-1);
}