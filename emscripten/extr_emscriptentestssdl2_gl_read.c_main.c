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
typedef  int /*<<< orphan*/  SDL_GLContext ;

/* Variables and functions */
 int /*<<< orphan*/  Draw () ; 
 int /*<<< orphan*/  Init () ; 
 int /*<<< orphan*/ * SDL_CreateWindow (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_GL_CreateContext (int /*<<< orphan*/ *) ; 
 char* SDL_GetError () ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 scalar_t__ SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_WINDOWPOS_UNDEFINED ; 
 int /*<<< orphan*/  SDL_WINDOW_OPENGL ; 
 int /*<<< orphan*/  Verify () ; 
 int /*<<< orphan*/  height ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  width ; 

int main(int argc, char *argv[])
{
  SDL_Window *window;
  SDL_GLContext context;

  if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow("sdl_gl_read", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

  if (!window) {
    printf("Unable to create window: %s\n", SDL_GetError());
    return 1;
  }

  context = SDL_GL_CreateContext(window);

  Init();
  Draw();
  Verify();

  return 0;
}