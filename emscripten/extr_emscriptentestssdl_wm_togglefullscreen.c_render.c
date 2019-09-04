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
struct TYPE_3__ {int member_2; int member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SDL_Rect ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_FillRect (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  emscripten_get_canvas_element_size (char*,int*,int*) ; 
 int /*<<< orphan*/  screen ; 

void render() {
  int width, height;
  emscripten_get_canvas_element_size("#canvas", &width, &height);
  SDL_Rect rect = { 0, 0, width, height };
  SDL_FillRect(screen, &rect, 0xff00ffff);
}