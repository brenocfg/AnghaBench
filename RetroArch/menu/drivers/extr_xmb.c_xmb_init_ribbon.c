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
typedef  int /*<<< orphan*/  xmb_handle_t ;
struct TYPE_3__ {float* color; float* vertex; float* tex_coord; float* lut_tex_coord; unsigned int vertices; } ;
typedef  TYPE_1__ video_coords_t ;
typedef  int /*<<< orphan*/  video_coord_array_t ;

/* Variables and functions */
 unsigned int XMB_RIBBON_COLS ; 
 int XMB_RIBBON_ROWS ; 
 unsigned int XMB_RIBBON_VERTICES ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (float*) ; 
 int /*<<< orphan*/ * menu_display_get_coords_array () ; 
 int /*<<< orphan*/  video_coord_array_append (int /*<<< orphan*/ *,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  xmb_ribbon_set_vertex (float*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void xmb_init_ribbon(xmb_handle_t * xmb)
{
   video_coords_t coords;
   unsigned r, c, col;
   unsigned i                = 0;
   video_coord_array_t *ca   = menu_display_get_coords_array();
   unsigned   vertices_total = XMB_RIBBON_VERTICES;
   float *dummy              = (float*)calloc(4 * vertices_total, sizeof(float));
   float *ribbon_verts       = (float*)calloc(2 * vertices_total, sizeof(float));

   /* Set up vertices */
   for (r = 0; r < XMB_RIBBON_ROWS - 1; r++)
   {
      for (c = 0; c < XMB_RIBBON_COLS; c++)
      {
         col = r % 2 ? XMB_RIBBON_COLS - c - 1 : c;
         xmb_ribbon_set_vertex(ribbon_verts, i,     r,     col);
         xmb_ribbon_set_vertex(ribbon_verts, i + 2, r + 1, col);
         i  += 4;
      }
   }

   coords.color         = dummy;
   coords.vertex        = ribbon_verts;
   coords.tex_coord     = dummy;
   coords.lut_tex_coord = dummy;
   coords.vertices      = vertices_total;

   video_coord_array_append(ca, &coords, coords.vertices);

   free(dummy);
   free(ribbon_verts);
}