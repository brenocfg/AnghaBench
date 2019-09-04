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

__attribute__((used)) static int
ttcompatspeedtab(int speed, struct speedtab *table)
{
	if (speed == 0)
		return (0); /* hangup */
	for ( ; table->sp_speed > 0; table++)
		if (table->sp_speed <= speed) /* nearest one, rounded down */
			return (table->sp_code);
	return (1); /* 50, min and not hangup */
}