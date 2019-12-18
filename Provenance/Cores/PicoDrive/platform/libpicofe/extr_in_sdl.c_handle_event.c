#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct in_sdl_state {int /*<<< orphan*/  keystate; } ;
struct TYPE_5__ {int sym; } ;
struct TYPE_6__ {TYPE_1__ keysym; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ key; } ;
typedef  TYPE_3__ SDL_Event ;

/* Variables and functions */
 scalar_t__ SDL_KEYDOWN ; 
 scalar_t__ SDL_KEYUP ; 
 int /*<<< orphan*/  update_keystate (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int handle_event(struct in_sdl_state *state, SDL_Event *event,
	int *kc_out, int *down_out)
{
	if (event->type != SDL_KEYDOWN && event->type != SDL_KEYUP)
		return -1;

	update_keystate(state->keystate, event->key.keysym.sym,
		event->type == SDL_KEYDOWN);
	if (kc_out != NULL)
		*kc_out = event->key.keysym.sym;
	if (down_out != NULL)
		*down_out = event->type == SDL_KEYDOWN;

	return 1;
}