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
struct TYPE_4__ {float const* color; float* vertex; float const* tex_coord; float const* lut_tex_coord; int vertices; } ;
typedef  TYPE_1__ video_coords_t ;
typedef  int /*<<< orphan*/  video_coord_array_t ;
struct TYPE_5__ {float* (* get_default_tex_coords ) () ;} ;

/* Variables and functions */
 TYPE_3__* menu_disp ; 
 int /*<<< orphan*/  menu_disp_ca ; 
 float* stub1 () ; 
 int /*<<< orphan*/  video_coord_array_append (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

void menu_display_push_quad(
      unsigned width, unsigned height,
      const float *colors, int x1, int y1,
      int x2, int y2)
{
   float vertex[8];
   video_coords_t coords;
   const float *coord_draw_ptr   = NULL;
   video_coord_array_t       *ca = &menu_disp_ca;

   vertex[0]             = x1 / (float)width;
   vertex[1]             = y1 / (float)height;
   vertex[2]             = x2 / (float)width;
   vertex[3]             = y1 / (float)height;
   vertex[4]             = x1 / (float)width;
   vertex[5]             = y2 / (float)height;
   vertex[6]             = x2 / (float)width;
   vertex[7]             = y2 / (float)height;

   if (menu_disp && menu_disp->get_default_tex_coords)
      coord_draw_ptr     = menu_disp->get_default_tex_coords();

   coords.color          = colors;
   coords.vertex         = vertex;
   coords.tex_coord      = coord_draw_ptr;
   coords.lut_tex_coord  = coord_draw_ptr;
   coords.vertices       = 3;

   video_coord_array_append(ca, &coords, 3);

   coords.color         += 4;
   coords.vertex        += 2;
   coords.tex_coord     += 2;
   coords.lut_tex_coord += 2;

   video_coord_array_append(ca, &coords, 3);
}