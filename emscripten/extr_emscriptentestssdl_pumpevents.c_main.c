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
 int /*<<< orphan*/  REPORT_RESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_INIT_EVERYTHING ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_SWSURFACE ; 
 int /*<<< orphan*/  SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ alphakey () ; 
 int /*<<< orphan*/  emscripten_run_script (char*) ; 
 scalar_t__ loop1 () ; 
 scalar_t__ loop2 () ; 
 int /*<<< orphan*/  result ; 

int main(int argc, char *argv[])
{
   SDL_Init(SDL_INIT_EVERYTHING);
   SDL_SetVideoMode(600, 400, 32, SDL_SWSURFACE);

   emscripten_run_script("keydown(37);"); // left
   result += loop1();
   emscripten_run_script("keydown(39);"); // right
   result += loop2();
   emscripten_run_script("keydown(65);"); // A
   result += alphakey();
   REPORT_RESULT(result);
   return 0;
}