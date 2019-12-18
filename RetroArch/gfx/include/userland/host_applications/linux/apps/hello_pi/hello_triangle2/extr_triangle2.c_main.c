#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int screen_width; int screen_height; } ;
typedef  int GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_host_init () ; 
 int /*<<< orphan*/  draw_mandelbrot_to_texture (TYPE_1__*,int,int,double) ; 
 int /*<<< orphan*/  draw_triangles (TYPE_1__*,int,int,double,int,int) ; 
 int get_mouse (TYPE_1__*,int*,int*) ; 
 int /*<<< orphan*/  init_ogl (TYPE_1__*) ; 
 int /*<<< orphan*/  init_shaders (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* state ; 

int main ()
{
   int terminate = 0;
   GLfloat cx, cy;
   bcm_host_init();

   // Clear application state
   memset( state, 0, sizeof( *state ) );

   // Start OGLES
   init_ogl(state);
   init_shaders(state);
   cx = state->screen_width/2;
   cy = state->screen_height/2;

   draw_mandelbrot_to_texture(state, cx, cy, 0.003);
   while (!terminate)
   {
      int x, y, b;
      b = get_mouse(state, &x, &y);
      if (b) break;
      draw_triangles(state, cx, cy, 0.003, x, y);
   }
   return 0;
}