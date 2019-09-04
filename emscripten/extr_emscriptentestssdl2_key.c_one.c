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
typedef  int /*<<< orphan*/  SDL_Event ;

/* Variables and functions */
 int /*<<< orphan*/  EventHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SDL_PollEvent (int /*<<< orphan*/ *) ; 

void one() {
#ifndef TEST_EMSCRIPTEN_SDL_SETEVENTHANDLER
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    EventHandler(0, &event);
  }
#endif
}