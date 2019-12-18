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
struct in_sdl_state {scalar_t__ joy; } ;
typedef  int /*<<< orphan*/  events ;
typedef  int Uint32 ;
typedef  int /*<<< orphan*/  SDL_Event ;

/* Variables and functions */
 int JOY_EVENTS ; 
 int SDL_ALLEVENTS ; 
 int /*<<< orphan*/  SDL_GETEVENT ; 
 int /*<<< orphan*/  SDL_PEEKEVENT ; 
 int SDL_PeepEvents (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDL_PumpEvents () ; 
 int /*<<< orphan*/  SDL_PushEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext_event_handler (int /*<<< orphan*/ *) ; 
 int handle_event (struct in_sdl_state*,int /*<<< orphan*/ *,int*,int*) ; 
 int handle_joy_event (struct in_sdl_state*,int /*<<< orphan*/ *,int*,int*) ; 

__attribute__((used)) static int collect_events(struct in_sdl_state *state, int *one_kc, int *one_down)
{
	SDL_Event events[4];
	Uint32 mask = state->joy ? JOY_EVENTS : (SDL_ALLEVENTS & ~JOY_EVENTS);
	int count, maxcount;
	int i, ret, retval = 0;
	int num_events, num_peeped_events;
	SDL_Event *event;

	maxcount = (one_kc != NULL) ? 1 : sizeof(events) / sizeof(events[0]);

	SDL_PumpEvents();

	num_events = SDL_PeepEvents(NULL, 0, SDL_PEEKEVENT, mask);

	for (num_peeped_events = 0; num_peeped_events < num_events; num_peeped_events += count) {
		count = SDL_PeepEvents(events, maxcount, SDL_GETEVENT, mask);
		if (count <= 0)
			break;
		for (i = 0; i < count; i++) {
			event = &events[i];
			if (state->joy)
				ret = handle_joy_event(state,
					event, one_kc, one_down);
			else
				ret = handle_event(state,
					event, one_kc, one_down);
			if (ret < 0) {
				switch (ret) {
					case -2:
						SDL_PushEvent(event);
						break;
					default:
						if (ext_event_handler != NULL)
							ext_event_handler(event);
						break;
				}
				continue;
			}

			retval |= ret;
			if (one_kc != NULL && ret)
			{
				// don't lose events other devices might want to handle
				for (i++; i < count; i++)
					SDL_PushEvent(&events[i]);
				goto out;
			}
		}
	}

out:
	return retval;
}