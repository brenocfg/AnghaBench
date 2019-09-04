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
struct TYPE_6__ {int button; } ;
struct TYPE_5__ {int timestamp; int windowID; int which; int x; int y; } ;
struct TYPE_7__ {int type; TYPE_2__ button; TYPE_1__ wheel; } ;
typedef  TYPE_3__ SDL_Event ;

/* Variables and functions */
 int SDL_BUTTON_MIDDLE ; 
 int SDL_BUTTON_WHEELDOWN ; 
 int SDL_BUTTON_WHEELUP ; 
#define  SDL_MOUSEBUTTONDOWN 129 
#define  SDL_MOUSEWHEEL 128 
 scalar_t__ SDL_PollEvent (TYPE_3__*) ; 
 int gotWheelButtonDown ; 
 int gotWheelButtonUp ; 
 int gotWheelClick ; 
 int gotWheelDown ; 
 int gotWheelUp ; 
 int /*<<< orphan*/  instruction () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  report_result (int) ; 

void main_tick()
{
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_MOUSEWHEEL:
        printf("SDL_MOUSEWHEEL: timestamp: %u, windowID: %u, which: %u, x: %d, y: %d\n", event.wheel.timestamp, event.wheel.windowID, event.wheel.which, event.wheel.x, event.wheel.y);
        if (!gotWheelUp)
        {
          if (event.wheel.y > 0 && event.wheel.y < 2) { gotWheelUp = 1; instruction(); }
          else if (event.wheel.y >= 2) { printf("The scroll amount was too large. Either you scrolled very fast or the normalization is not working."); report_result(1); }
          else if (event.wheel.y < 0) { printf("You scrolled to the wrong direction (downwards)!\n"); report_result(1); }
        }
        else if (!gotWheelDown)
        {
          if (event.wheel.y < 0 && event.wheel.y > -2) { gotWheelDown = 1; instruction(); }
          else if (event.wheel.y <= -2) { printf("The scroll amount was too large. Either you scrolled very fast or the normalization is not working."); report_result(1); }
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        printf("SDL_MOUSEBUTTONDOWN: button: %d\n", event.button.button);
        if (event.button.button == SDL_BUTTON_WHEELDOWN) { printf("SDL_BUTTON_WHEELDOWN\n"); gotWheelButtonDown = 1; instruction(); }
        else if (event.button.button == SDL_BUTTON_WHEELUP) { printf("SDL_BUTTON_WHEELUP\n"); gotWheelButtonUp = 1; instruction(); }
        else if (event.button.button == SDL_BUTTON_MIDDLE) { printf("SDL_BUTTON_MIDDLE\n"); gotWheelClick = 1; instruction(); }
        break;
    }
  }
}