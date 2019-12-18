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
struct TYPE_8__ {int /*<<< orphan*/  model; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_host_init () ; 
 int /*<<< orphan*/  exit_func () ; 
 int /*<<< orphan*/  init_model_proj (TYPE_1__*) ; 
 int /*<<< orphan*/  init_ogl (TYPE_1__*) ; 
 int /*<<< orphan*/  init_textures (TYPE_1__*) ; 
 int /*<<< orphan*/  load_wavefront (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  redraw_scene (TYPE_1__*) ; 
 TYPE_1__* state ; 
 int /*<<< orphan*/  terminate ; 
 int /*<<< orphan*/  update_model (TYPE_1__*) ; 

int main ()
{
   bcm_host_init();
   printf("Note: ensure you have sufficient gpu_mem configured\n");

   // Clear application state
   memset( state, 0, sizeof( *state ) );

   // Start OGLES
   init_ogl(state);

   // Setup the model world
   init_model_proj(state);

   // initialise the OGLES texture(s)
   init_textures(state);

   //state->model = cube_wavefront();
   state->model = load_wavefront("/opt/vc/src/hello_pi/hello_teapot/teapot.obj.dat", NULL);

   while (!terminate)
   {
      update_model(state);
      redraw_scene(state);
   }
   exit_func();
   return 0;
}