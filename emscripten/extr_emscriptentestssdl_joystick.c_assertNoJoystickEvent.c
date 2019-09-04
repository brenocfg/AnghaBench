#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ SDL_Event ;

/* Variables and functions */
#define  SDL_JOYAXISMOTION 130 
#define  SDL_JOYBUTTONDOWN 129 
#define  SDL_JOYBUTTONUP 128 
 scalar_t__ SDL_PollEvent (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void assertNoJoystickEvent() {
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_JOYBUTTONDOWN: case SDL_JOYBUTTONUP: case SDL_JOYAXISMOTION: {
        // Fail.
        assert(0);
      }
    }
  }
}