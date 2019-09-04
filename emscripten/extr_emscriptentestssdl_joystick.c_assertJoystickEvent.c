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
struct TYPE_5__ {int which; int button; int state; } ;
struct TYPE_6__ {int which; int axis; int value; } ;
struct TYPE_7__ {int type; TYPE_1__ jbutton; TYPE_2__ jaxis; } ;
typedef  TYPE_3__ SDL_Event ;

/* Variables and functions */
#define  SDL_JOYAXISMOTION 130 
#define  SDL_JOYBUTTONDOWN 129 
#define  SDL_JOYBUTTONUP 128 
 int SDL_PollEvent (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 

void assertJoystickEvent(int expectedGamepad, int expectedType, int expectedIndex, int expectedValue) {
  SDL_Event event;
  while(1) {
    // Loop ends either when assertion fails (we run out of events), or we find
    // the event we're looking for.
    assert(SDL_PollEvent(&event) == 1);
    if (event.type != expectedType) {
      continue;
    }
    switch(event.type) {
      case SDL_JOYAXISMOTION: {
        assert(event.jaxis.which == expectedGamepad);
        assert(event.jaxis.axis == expectedIndex);
        assert(event.jaxis.value == expectedValue);
        break;
      }
      case SDL_JOYBUTTONUP: case SDL_JOYBUTTONDOWN: {
        assert(event.jbutton.which == expectedGamepad);
        assert(event.jbutton.button == expectedIndex);
        assert(event.jbutton.state == expectedValue);
        break;
      }
    }
    // Break out of while loop.
    break;
  }
}