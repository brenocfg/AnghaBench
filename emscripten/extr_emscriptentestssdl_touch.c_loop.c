#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; } ;
struct TYPE_4__ {int timestamp; float x; float y; float pressure; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  fingerId; int /*<<< orphan*/  touchId; } ;
typedef  TYPE_1__ SDL_TouchFingerEvent ;
typedef  TYPE_2__ SDL_Event ;

/* Variables and functions */
#define  SDL_FINGERDOWN 130 
#define  SDL_FINGERMOTION 129 
#define  SDL_FINGERUP 128 
 scalar_t__ SDL_PollEvent (TYPE_2__*) ; 
 char* TouchFingerTypeToString (int) ; 
 int got_down ; 
 int got_move ; 
 int got_up ; 
 int /*<<< orphan*/  printf (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  progress () ; 

void loop() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_FINGERMOTION:
      case SDL_FINGERDOWN:
      case SDL_FINGERUP: {
        SDL_TouchFingerEvent *t = (SDL_TouchFingerEvent*)&event;
        printf("type: %s, timestamp: %u, touchId: %llu, fingerId: %llu, x: %f, y: %f, dx: %f, dy: %f, pressure: %f\n",
          TouchFingerTypeToString(event.type), t->timestamp, t->touchId, t->fingerId, t->x, t->y, t->dx, t->dy, t->pressure);

        if (t->timestamp != 0 && t->x >= 0.f && t->x <= 1.f && t->y >= 0.f && t->y <= 1.f && t->pressure >= 0.f && t->pressure <= 1.f) {
          if (event.type == SDL_FINGERDOWN) { got_down = 1; progress(); }
          if (event.type == SDL_FINGERMOTION) { got_move = 1; progress(); }
          if (event.type == SDL_FINGERDOWN) { got_up = 1; progress(); }
        }
        break;
      }
    }
  }
}