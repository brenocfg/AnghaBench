#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int type; } ;
struct TYPE_7__ {int button; int state; int x; int y; } ;
struct TYPE_6__ {int x; int y; int xrel; int yrel; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ SDL_MouseMotionEvent ;
typedef  TYPE_2__ SDL_MouseButtonEvent ;
typedef  TYPE_3__ SDL_Event ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_RESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_GETEVENT ; 
 int /*<<< orphan*/  SDL_GetMouseState (int*,int*) ; 
#define  SDL_MOUSEBUTTONDOWN 130 
#define  SDL_MOUSEBUTTONUP 129 
#define  SDL_MOUSEMOTION 128 
 int SDL_PeepEvents (TYPE_3__*,int,int /*<<< orphan*/ ,int const,int const) ; 
 scalar_t__ SDL_PollEvent (TYPE_3__*) ; 
 int abs (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emscripten_run_script (char*) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 
 int /*<<< orphan*/  result ; 

void one() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_MOUSEMOTION: {
        SDL_MouseMotionEvent *m = (SDL_MouseMotionEvent*)&event;
        assert(m->state == 0);
        int x, y;
        SDL_GetMouseState(&x, &y);
        assert(x == m->x && y == m->y);
        printf("motion: %d,%d  %d,%d\n", m->x, m->y, m->xrel, m->yrel);
#ifdef TEST_SDL_MOUSE_OFFSETS
        assert( (abs(m->x-5) <= 1 && abs(m->y-15) <= 1 && abs(m->xrel-5) <= 1 && abs(m->yrel-15) <= 1)
            ||  (abs(m->x-25) <= 1 && abs(m->y-72) <= 1 && abs(m->xrel-20) <= 1 && abs(m->yrel-57) <= 1) );
#else
        assert( (abs(m->x-10) <= 1 && abs(m->y-20) <= 1 && abs(m->xrel-10) <= 1 && abs(m->yrel-20) <= 1)
            ||  (abs(m->x-30) <= 1 && abs(m->y-77) <= 1 && abs(m->xrel-20) <= 1 && abs(m->yrel-57) <= 1) );
#endif
        break;
      }
      case SDL_MOUSEBUTTONDOWN: {
        SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent*)&event;
        if (m->button == 2) {
          REPORT_RESULT(result);
          emscripten_run_script("throw 'done'");
        }
        printf("button down: %d,%d  %d,%d\n", m->button, m->state, m->x, m->y);
#ifdef TEST_SDL_MOUSE_OFFSETS
        assert(m->button == 1 && m->state == 1 && abs(m->x-5) <= 1 && abs(m->y-15) <= 1);
#else
        assert(m->button == 1 && m->state == 1 && abs(m->x-10) <= 1 && abs(m->y-20) <= 1);
#endif
        break;
      }
      case SDL_MOUSEBUTTONUP: {
        SDL_MouseButtonEvent *m = (SDL_MouseButtonEvent*)&event;
        printf("button up: %d,%d  %d,%d\n", m->button, m->state, m->x, m->y);
#ifdef TEST_SDL_MOUSE_OFFSETS
        assert(m->button == 1 && m->state == 0 && abs(m->x-5) <= 1 && abs(m->y-15) <= 1);
#else
        assert(m->button == 1 && m->state == 0 && abs(m->x-10) <= 1 && abs(m->y-20) <= 1);
#endif
        // Remove another click we want to ignore
        assert(SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONDOWN) == 1);
        assert(SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_MOUSEBUTTONUP, SDL_MOUSEBUTTONUP) == 1);
        break;
      }
    }
  }
}