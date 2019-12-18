#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ scene_state; } ;
struct TYPE_4__ {void* rot_angle_z; void* rot_angle_y; void* rot_angle_x; int /*<<< orphan*/  distance; int /*<<< orphan*/  distance_inc; int /*<<< orphan*/  rot_angle_z_inc; int /*<<< orphan*/  rot_angle_y_inc; int /*<<< orphan*/  rot_angle_x_inc; } ;
typedef  TYPE_1__ TEAPOT_STATE_T ;
typedef  TYPE_2__ RASPITEX_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glRotatef (void*,float,float,float) ; 
 int /*<<< orphan*/  glTranslatef (float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_and_clip_distance (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* inc_and_wrap_angle (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int teapot_update_model(RASPITEX_STATE *raspitex_state)
{
   TEAPOT_STATE_T *state = (TEAPOT_STATE_T *) raspitex_state->scene_state;

   // update position
   state->rot_angle_x = inc_and_wrap_angle(state->rot_angle_x, state->rot_angle_x_inc);
   state->rot_angle_y = inc_and_wrap_angle(state->rot_angle_y, state->rot_angle_y_inc);
   state->rot_angle_z = inc_and_wrap_angle(state->rot_angle_z, state->rot_angle_z_inc);
   state->distance    = inc_and_clip_distance(state->distance, state->distance_inc);

   glLoadIdentity();
   // move camera back to see the cube
   glTranslatef(0.f, 0.f, -state->distance);

   // Rotate model to new position
   glRotatef(state->rot_angle_x, 1.f, 0.f, 0.f);
   glRotatef(state->rot_angle_y, 0.f, 1.f, 0.f);
   glRotatef(state->rot_angle_z, 0.f, 0.f, 1.f);

   return 0;
}