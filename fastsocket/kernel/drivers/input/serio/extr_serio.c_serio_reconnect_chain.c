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
struct serio {struct serio* child; } ;

/* Variables and functions */
 scalar_t__ serio_reconnect_port (struct serio*) ; 

__attribute__((used)) static void serio_reconnect_chain(struct serio *serio)
{
	do {
		if (serio_reconnect_port(serio)) {
			/* Ok, old children are now gone, we are done */
			break;
		}
		serio = serio->child;
	} while (serio);
}