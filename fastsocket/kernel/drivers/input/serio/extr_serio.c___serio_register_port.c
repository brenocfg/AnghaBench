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
struct serio {int dummy; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SERIO_REGISTER_PORT ; 
 int /*<<< orphan*/  serio_init_port (struct serio*) ; 
 int /*<<< orphan*/  serio_queue_event (struct serio*,struct module*,int /*<<< orphan*/ ) ; 

void __serio_register_port(struct serio *serio, struct module *owner)
{
	serio_init_port(serio);
	serio_queue_event(serio, owner, SERIO_REGISTER_PORT);
}