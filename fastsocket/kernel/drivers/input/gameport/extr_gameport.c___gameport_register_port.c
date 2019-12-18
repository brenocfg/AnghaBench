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
struct module {int dummy; } ;
struct gameport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMEPORT_REGISTER_PORT ; 
 int /*<<< orphan*/  gameport_init_port (struct gameport*) ; 
 int /*<<< orphan*/  gameport_queue_event (struct gameport*,struct module*,int /*<<< orphan*/ ) ; 

void __gameport_register_port(struct gameport *gameport, struct module *owner)
{
	gameport_init_port(gameport);
	gameport_queue_event(gameport, owner, GAMEPORT_REGISTER_PORT);
}