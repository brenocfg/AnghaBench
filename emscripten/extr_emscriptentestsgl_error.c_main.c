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
typedef  int /*<<< orphan*/  SDL_Surface ;

/* Variables and functions */
 scalar_t__ GL_STACK_UNDERFLOW ; 
 int /*<<< orphan*/  REPORT_RESULT (int) ; 
 int /*<<< orphan*/  SDL_GL_DOUBLEBUFFER ; 
 int /*<<< orphan*/  SDL_GL_SetAttribute (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 scalar_t__ SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_OPENGL ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ glGetError () ; 
 int /*<<< orphan*/  glPopMatrix () ; 

int main()
{
  SDL_Surface *screen;

  assert(SDL_Init(SDL_INIT_VIDEO) == 0);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  screen = SDL_SetVideoMode( 256, 256, 16, SDL_OPENGL );
  assert(screen);

  // pop from empty stack
  glPopMatrix();
  assert(glGetError() == GL_STACK_UNDERFLOW);

  REPORT_RESULT(1);
  return 0;
}