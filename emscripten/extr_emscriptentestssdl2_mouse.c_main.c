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
typedef  int /*<<< orphan*/  SDL_Window ;
typedef  int /*<<< orphan*/  SDL_Renderer ;
typedef  TYPE_1__ SDL_Rect ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_CreateWindowAndRenderer (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_RenderFillRect (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_SetRenderDrawColor (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  emscripten_async_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  main_2 ; 

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window;
  SDL_Renderer *renderer;

  SDL_CreateWindowAndRenderer(600, 450, 0, &window, &renderer);

  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF );
  SDL_Rect rect = { 0, 0, 600, 450 };
  SDL_RenderFillRect(renderer, &rect);

  emscripten_async_call(main_2, NULL, 3000); // avoid startup delays and intermittent errors

  return 0;
}