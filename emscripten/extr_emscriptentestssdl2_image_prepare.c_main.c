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
typedef  int /*<<< orphan*/  SDL_Window ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_CreateWindowAndRenderer (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ emscripten_run_preload_plugins (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  ready ; 
 int /*<<< orphan*/  rename (char*,char*) ; 
 int /*<<< orphan*/  renderer ; 

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window;

  SDL_CreateWindowAndRenderer(600, 450, 0, &window, &renderer);

  printf("rename..\n");

  rename("screenshot.not", "screenshot.jpg");

  printf("prepare..\n");

  assert(emscripten_run_preload_plugins("screenshot.jpg", ready, NULL) == 0);

  return 0;
}