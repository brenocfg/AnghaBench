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
struct TYPE_5__ {int sym; int mod; int scancode; } ;
struct TYPE_6__ {TYPE_1__ keysym; } ;
struct TYPE_7__ {int type; TYPE_2__ key; } ;
typedef  TYPE_3__ SDL_Event ;

/* Variables and functions */
 int KMOD_LALT ; 
 int KMOD_LCTRL ; 
 int KMOD_LSHIFT ; 
 int KMOD_RALT ; 
 int KMOD_RCTRL ; 
 int KMOD_RSHIFT ; 
 int /*<<< orphan*/  REPORT_RESULT (int) ; 
#define  SDLK_DOWN 134 
 int SDLK_LALT ; 
 int SDLK_LCTRL ; 
#define  SDLK_LEFT 133 
 int SDLK_LSHIFT ; 
#define  SDLK_RIGHT 132 
#define  SDLK_UP 131 
#define  SDLK_a 130 
#define  SDL_KEYDOWN 129 
#define  SDL_KEYUP 128 
 scalar_t__ SDL_PollEvent (TYPE_3__*) ; 
 int SDL_SCANCODE_B ; 
 int /*<<< orphan*/  emscripten_run_script (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int result ; 

void one() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    printf("got event %d\n", event.type);
    switch(event.type) {
      case SDL_KEYDOWN:
        break;
      case SDL_KEYUP:
        // don't handle the modifier key events
        if (event.key.keysym.sym == SDLK_LCTRL ||
            event.key.keysym.sym == SDLK_LSHIFT ||
            event.key.keysym.sym == SDLK_LALT) {
          return;
        }
        if ((event.key.keysym.mod & KMOD_LCTRL) || (event.key.keysym.mod & KMOD_RCTRL)) {
          result *= 2;
        }
        if ((event.key.keysym.mod & KMOD_LSHIFT) || (event.key.keysym.mod & KMOD_RSHIFT)) {
          result *= 3;
        }
        if ((event.key.keysym.mod & KMOD_LALT) || (event.key.keysym.mod & KMOD_RALT)) {
          result *= 5;
        }
        switch (event.key.keysym.sym) {
          case SDLK_RIGHT: printf("right\n"); result *= 7; break;
          case SDLK_LEFT: printf("left\n"); result *= 11; break;
          case SDLK_DOWN: printf("down\n"); result *= 13; break;
          case SDLK_UP: printf("up\n"); result *= 17; break;
          case SDLK_a: printf("a\n"); result *= 19; break;
          default: {
            if (event.key.keysym.scancode == SDL_SCANCODE_B) {
              printf("b scancode\n"); result *= 23; break;
            }
            printf("unknown key: sym %d scancode %d\n", event.key.keysym.sym, event.key.keysym.scancode);
            REPORT_RESULT(result);
            emscripten_run_script("throw 'done'"); // comment this out to leave event handling active. Use the following to log DOM keys:
                                                   // addEventListener('keyup', function(event) { console.log(event.keyCode) }, true)
          }
        }
        break;
      default: /* Report an unhandled event */
        printf("I don't know what this event is!\n");
    }
  }
}