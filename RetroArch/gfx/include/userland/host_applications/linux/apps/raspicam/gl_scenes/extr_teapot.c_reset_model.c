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
struct TYPE_3__ {float rot_angle_x; float rot_angle_y; float rot_angle_z; float rot_angle_x_inc; float rot_angle_y_inc; float rot_angle_z_inc; float distance; } ;
typedef  TYPE_1__ TEAPOT_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_model(TEAPOT_STATE_T *state)
{
   // reset model position
   glMatrixMode(GL_MODELVIEW);

   // reset model rotation
   state->rot_angle_x = 45.f; state->rot_angle_y = 30.f; state->rot_angle_z = 0.f;
   state->rot_angle_x_inc = 0.5f; state->rot_angle_y_inc = 0.5f; state->rot_angle_z_inc = 0.f;
   state->distance = 0.8f*1.5f;
}