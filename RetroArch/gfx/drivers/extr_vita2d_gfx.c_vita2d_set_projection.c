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
struct TYPE_3__ {float rotation; int /*<<< orphan*/  mvp_no_rot; int /*<<< orphan*/  mvp; } ;
typedef  TYPE_1__ vita_video_t ;
struct video_ortho {int /*<<< orphan*/  zfar; int /*<<< orphan*/  znear; int /*<<< orphan*/  top; int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
typedef  int /*<<< orphan*/  math_matrix_4x4 ;

/* Variables and functions */
 float M_PI ; 
 int /*<<< orphan*/  matrix_4x4_multiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_4x4_ortho (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_4x4_rotate_z (int /*<<< orphan*/ ,float) ; 

__attribute__((used)) static void vita2d_set_projection(vita_video_t *vita,
      struct video_ortho *ortho, bool allow_rotate)
{
   math_matrix_4x4 rot;

   /* Calculate projection. */
   matrix_4x4_ortho(vita->mvp_no_rot, ortho->left, ortho->right,
         ortho->bottom, ortho->top, ortho->znear, ortho->zfar);

   if (!allow_rotate)
   {
      vita->mvp = vita->mvp_no_rot;
      return;
   }

   matrix_4x4_rotate_z(rot, M_PI * vita->rotation / 180.0f);
   matrix_4x4_multiply(vita->mvp, rot, vita->mvp_no_rot);
}