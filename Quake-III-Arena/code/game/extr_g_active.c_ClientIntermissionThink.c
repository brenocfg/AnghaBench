#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int buttons; } ;
struct TYPE_6__ {TYPE_3__ cmd; } ;
struct TYPE_7__ {int /*<<< orphan*/  eFlags; } ;
struct TYPE_9__ {int oldbuttons; int buttons; int readyToExit; TYPE_1__ pers; TYPE_2__ ps; } ;
typedef  TYPE_4__ gclient_t ;

/* Variables and functions */
 int BUTTON_ATTACK ; 
 int BUTTON_USE_HOLDABLE ; 
 int /*<<< orphan*/  EF_FIRING ; 
 int /*<<< orphan*/  EF_TALK ; 

void ClientIntermissionThink( gclient_t *client ) {
	client->ps.eFlags &= ~EF_TALK;
	client->ps.eFlags &= ~EF_FIRING;

	// the level will exit when everyone wants to or after timeouts

	// swap and latch button actions
	client->oldbuttons = client->buttons;
	client->buttons = client->pers.cmd.buttons;
	if ( client->buttons & ( BUTTON_ATTACK | BUTTON_USE_HOLDABLE ) & ( client->oldbuttons ^ client->buttons ) ) {
		// this used to be an ^1 but once a player says ready, it should stick
		client->readyToExit = 1;
	}
}