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

/* Variables and functions */
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_SWSURFACE ; 
 int /*<<< orphan*/  SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ emscripten_run_preload_plugins (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  ready ; 
 int /*<<< orphan*/  rename (char*,char*) ; 
 int /*<<< orphan*/  screen ; 

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(600, 450, 32, SDL_SWSURFACE);

  printf("rename..\n");

  rename("screenshot.not", "screenshot.jpg");

  printf("prepare..\n");

  assert(emscripten_run_preload_plugins("screenshot.jpg", ready, NULL) == 0);

  return 0;
}