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
struct in_sdl_state {int* axis_keydown; int /*<<< orphan*/  keystate; int /*<<< orphan*/  joy_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; scalar_t__ button; int /*<<< orphan*/  which; } ;
struct TYPE_5__ {int axis; int value; int /*<<< orphan*/  which; } ;
struct TYPE_7__ {int type; TYPE_2__ jbutton; TYPE_1__ jaxis; } ;
typedef  TYPE_3__ SDL_Event ;

/* Variables and functions */
 int SDLK_DOWN ; 
 int SDLK_LEFT ; 
 int SDLK_RIGHT ; 
 int SDLK_UP ; 
 int /*<<< orphan*/  SDLK_WORLD_0 ; 
#define  SDL_JOYAXISMOTION 130 
#define  SDL_JOYBUTTONDOWN 129 
#define  SDL_JOYBUTTONUP 128 
 int /*<<< orphan*/  SDL_PRESSED ; 
 int /*<<< orphan*/  update_keystate (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int handle_joy_event(struct in_sdl_state *state, SDL_Event *event,
	int *kc_out, int *down_out)
{
	int kc = -1, down = 0, ret = 0;

	/* TODO: remaining axis */
	switch (event->type) {
	case SDL_JOYAXISMOTION:
		if (event->jaxis.which != state->joy_id)
			return -2;
		if (event->jaxis.axis > 1)
			break;
		if (-16384 <= event->jaxis.value && event->jaxis.value <= 16384) {
			kc = state->axis_keydown[event->jaxis.axis];
			state->axis_keydown[event->jaxis.axis] = 0;
			ret = 1;
		}
		else if (event->jaxis.value < -16384) {
			kc = state->axis_keydown[event->jaxis.axis];
			if (kc)
				update_keystate(state->keystate, kc, 0);
			kc = event->jaxis.axis ? SDLK_UP : SDLK_LEFT;
			state->axis_keydown[event->jaxis.axis] = kc;
			down = 1;
			ret = 1;
		}
		else if (event->jaxis.value > 16384) {
			kc = state->axis_keydown[event->jaxis.axis];
			if (kc)
				update_keystate(state->keystate, kc, 0);
			kc = event->jaxis.axis ? SDLK_DOWN : SDLK_RIGHT;
			state->axis_keydown[event->jaxis.axis] = kc;
			down = 1;
			ret = 1;
		}
		break;

	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
		if (event->jbutton.which != state->joy_id)
			return -2;
		kc = (int)event->jbutton.button + SDLK_WORLD_0;
		down = event->jbutton.state == SDL_PRESSED;
		ret = 1;
		break;
	default:
		return -1;
	}

	if (ret)
		update_keystate(state->keystate, kc, down);
	if (kc_out != NULL)
		*kc_out = kc;
	if (down_out != NULL)
		*down_out = down;

	return ret;
}