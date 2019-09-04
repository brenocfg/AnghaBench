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
 int /*<<< orphan*/  SDL_HWSURFACE ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_StartTextInput () ; 
 int /*<<< orphan*/  emscripten_run_script (char*) ; 
 int /*<<< orphan*/  one () ; 

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_SetVideoMode(600, 450, 32, SDL_HWSURFACE);
  SDL_StartTextInput();

  emscripten_run_script("simulateKeyEvent('a'.charCodeAt(0))"); // a
  emscripten_run_script("simulateKeyEvent('A'.charCodeAt(0))"); // A

  one();

  return 0;
}