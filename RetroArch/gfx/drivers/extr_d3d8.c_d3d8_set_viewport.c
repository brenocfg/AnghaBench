#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct d3d_matrix {int dummy; } ;
struct TYPE_3__ {int X; int Y; unsigned int Width; unsigned int Height; float MinZ; float MaxZ; } ;
struct TYPE_4__ {double dev_rotation; int /*<<< orphan*/  mvp_rotate; int /*<<< orphan*/  mvp; TYPE_1__ final_viewport; } ;
typedef  TYPE_2__ d3d8_video_t ;

/* Variables and functions */
 double M_PI ; 
 int /*<<< orphan*/  d3d8_calculate_rect (void*,unsigned int*,unsigned int*,int*,int*,int,int) ; 
 int /*<<< orphan*/  d3d_matrix_identity (struct d3d_matrix*) ; 
 int /*<<< orphan*/  d3d_matrix_multiply (struct d3d_matrix*,struct d3d_matrix*,struct d3d_matrix*) ; 
 int /*<<< orphan*/  d3d_matrix_ortho_off_center_lh (struct d3d_matrix*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,float,float) ; 
 int /*<<< orphan*/  d3d_matrix_rotation_z (struct d3d_matrix*,double) ; 
 int /*<<< orphan*/  d3d_matrix_transpose (int /*<<< orphan*/ *,struct d3d_matrix*) ; 

__attribute__((used)) static void d3d8_set_viewport(void *data,
      unsigned width, unsigned height,
      bool force_full,
      bool allow_rotate)
{
   struct d3d_matrix proj, ortho, rot, matrix;
   int x               = 0;
   int y               = 0;
   d3d8_video_t *d3d = (d3d8_video_t*)data;

   d3d8_calculate_rect(data, &width, &height, &x, &y,
         force_full, allow_rotate);

   /* D3D doesn't support negative X/Y viewports ... */
   if (x < 0)
      x = 0;
   if (y < 0)
      y = 0;

   d3d->final_viewport.X      = x;
   d3d->final_viewport.Y      = y;
   d3d->final_viewport.Width  = width;
   d3d->final_viewport.Height = height;
   d3d->final_viewport.MinZ   = 0.0f;
   d3d->final_viewport.MaxZ   = 0.0f;

   d3d_matrix_ortho_off_center_lh(&ortho, 0, 1, 0, 1, 0.0f, 1.0f);
   d3d_matrix_identity(&rot);
   d3d_matrix_rotation_z(&rot, d3d->dev_rotation * (M_PI / 2.0));
   d3d_matrix_multiply(&proj, &ortho, &rot);
   d3d_matrix_transpose(&d3d->mvp, &ortho);
   d3d_matrix_transpose(&d3d->mvp_rotate, &matrix);
}