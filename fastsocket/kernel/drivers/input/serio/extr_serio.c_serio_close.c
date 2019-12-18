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
struct serio {int /*<<< orphan*/  (* close ) (struct serio*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  serio_set_drv (struct serio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct serio*) ; 

void serio_close(struct serio *serio)
{
	if (serio->close)
		serio->close(serio);

	serio_set_drv(serio, NULL);
}