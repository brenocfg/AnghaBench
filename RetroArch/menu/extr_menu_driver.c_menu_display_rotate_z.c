#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_4__ {int /*<<< orphan*/ * matrix; int /*<<< orphan*/  scale_z; int /*<<< orphan*/  scale_y; int /*<<< orphan*/  scale_x; int /*<<< orphan*/  scale_enable; int /*<<< orphan*/  rotation; } ;
typedef  TYPE_1__ menu_display_ctx_rotate_draw_t ;
typedef  int /*<<< orphan*/  math_matrix_4x4 ;
struct TYPE_5__ {scalar_t__ (* get_default_mvp ) (int /*<<< orphan*/ *) ;scalar_t__ handles_transform; } ;

/* Variables and functions */
 int /*<<< orphan*/  matrix_4x4_multiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_4x4_rotate_z (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_4x4_scale (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* menu_disp ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 

void menu_display_rotate_z(menu_display_ctx_rotate_draw_t *draw,
      video_frame_info_t *video_info)
{
   math_matrix_4x4 matrix_rotated, matrix_scaled;
   math_matrix_4x4 *b = NULL;

   if (
         !draw                       ||
         !menu_disp                  ||
         !menu_disp->get_default_mvp ||
         menu_disp->handles_transform
      )
      return;

   b = (math_matrix_4x4*)menu_disp->get_default_mvp(video_info);

   if (!b)
      return;

   matrix_4x4_rotate_z(matrix_rotated, draw->rotation);
   matrix_4x4_multiply(*draw->matrix, matrix_rotated, *b);

   if (!draw->scale_enable)
      return;

   matrix_4x4_scale(matrix_scaled,
         draw->scale_x, draw->scale_y, draw->scale_z);
   matrix_4x4_multiply(*draw->matrix, matrix_scaled, *draw->matrix);
}