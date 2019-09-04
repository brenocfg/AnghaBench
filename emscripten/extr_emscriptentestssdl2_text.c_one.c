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
struct TYPE_4__ {char* text; } ;
struct TYPE_5__ {int type; TYPE_1__ text; } ;
typedef  TYPE_2__ SDL_Event ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_RESULT (int) ; 
 scalar_t__ SDL_PollEvent (TYPE_2__*) ; 
#define  SDL_TEXTEDITING 129 
#define  SDL_TEXTINPUT 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_run_script (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int result ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void one() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_TEXTEDITING: assert(0); break;
      case SDL_TEXTINPUT:
        printf("Received %s\n", event.text.text);
        if (!strcmp("a", event.text.text)) {
          result = 1;
        } else if (!strcmp("A", event.text.text)) {
          REPORT_RESULT(result);
          emscripten_run_script("throw 'done'");
        }
        break;
    }
  }
}