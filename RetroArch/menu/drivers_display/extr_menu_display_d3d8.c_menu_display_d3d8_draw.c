#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {double width; double height; scalar_t__ userdata; } ;
typedef  TYPE_4__ video_frame_info_t ;
struct TYPE_15__ {scalar_t__ id; } ;
struct TYPE_19__ {double width; double height; double x; double y; scalar_t__ prim_type; TYPE_3__* coords; scalar_t__ texture; scalar_t__ matrix_data; TYPE_1__ pipeline; } ;
typedef  TYPE_5__ menu_display_ctx_draw_t ;
typedef  int /*<<< orphan*/  math_matrix_4x4 ;
struct TYPE_16__ {unsigned int offset; int /*<<< orphan*/  buffer; scalar_t__ size; } ;
struct TYPE_20__ {TYPE_2__ menu_display; int /*<<< orphan*/  dev; int /*<<< orphan*/  mvp_transposed; } ;
typedef  TYPE_6__ d3d8_video_t ;
struct TYPE_21__ {float z; int /*<<< orphan*/  color; int /*<<< orphan*/  v; int /*<<< orphan*/  u; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_7__ Vertex ;
struct TYPE_22__ {int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; } ;
struct TYPE_17__ {unsigned int vertices; float* vertex; float* tex_coord; float* color; } ;
typedef  TYPE_8__ D3DSURFACE_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  D3DCOLOR_ARGB (int,int,int,int) ; 
 scalar_t__ MENU_DISPLAY_PRIM_TRIANGLESTRIP ; 
 int /*<<< orphan*/  d3d8_draw_primitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  d3d8_set_mvp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ d3d8_texture_get_level_desc (void*,int /*<<< orphan*/ ,TYPE_8__*) ; 
 scalar_t__ d3d8_vertex_buffer_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d8_vertex_buffer_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d_matrix_transpose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  matrix_4x4_multiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_4x4_scale (int /*<<< orphan*/ ,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_4x4_translate (int /*<<< orphan*/ ,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_display_d3d8_bind_texture (TYPE_5__*,TYPE_6__*) ; 
 scalar_t__ menu_display_d3d8_get_default_mvp (TYPE_4__*) ; 
 float* menu_display_d3d8_get_default_tex_coords () ; 
 float* menu_display_d3d8_get_default_vertices () ; 
 int /*<<< orphan*/  menu_display_prim_to_d3d8_enum (scalar_t__) ; 

__attribute__((used)) static void menu_display_d3d8_draw(menu_display_ctx_draw_t *draw,
      video_frame_info_t *video_info)
{
   unsigned i;
   math_matrix_4x4 mop, m1, m2;
   d3d8_video_t *d3d             = (d3d8_video_t*)video_info->userdata;
   Vertex * pv                   = NULL;
   const float *vertex           = NULL;
   const float *tex_coord        = NULL;
   const float *color            = NULL;

   if (!d3d || !draw || draw->pipeline.id)
      return;
   if((d3d->menu_display.offset + draw->coords->vertices )
         > (unsigned)d3d->menu_display.size)
      return;

   pv           = (Vertex*)
      d3d8_vertex_buffer_lock(d3d->menu_display.buffer);

   if (!pv)
      return;

   pv          += d3d->menu_display.offset;
   vertex       = draw->coords->vertex;
   tex_coord    = draw->coords->tex_coord;
   color        = draw->coords->color;

   if (!vertex)
      vertex    = menu_display_d3d8_get_default_vertices();
   if (!tex_coord)
      tex_coord = menu_display_d3d8_get_default_tex_coords();

   for (i = 0; i < draw->coords->vertices; i++)
   {
      int colors[4];

      colors[0]   = *color++ * 0xFF;
      colors[1]   = *color++ * 0xFF;
      colors[2]   = *color++ * 0xFF;
      colors[3]   = *color++ * 0xFF;

      pv[i].x     = *vertex++;
      pv[i].y     = *vertex++;
      pv[i].z     = 0.5f;
      pv[i].u     = *tex_coord++;
      pv[i].v     = *tex_coord++;

#if 1
	  if ((void*)draw->texture)
      {
         D3DSURFACE_DESC desc;
         if (d3d8_texture_get_level_desc((void*)draw->texture, 0, &desc))
         {
            pv[i].u *= desc.Width;
            pv[i].v *= desc.Height;
         }
      }
#endif

      pv[i].color =
         D3DCOLOR_ARGB(
               colors[3], /* A */
               colors[0], /* R */
               colors[1], /* G */
               colors[2]  /* B */
               );
   }
   d3d8_vertex_buffer_unlock(d3d->menu_display.buffer);

   if(!draw->matrix_data)
      draw->matrix_data = menu_display_d3d8_get_default_mvp(video_info);

   /* ugh */
   matrix_4x4_scale(m1,       2.0,  2.0, 0);
   matrix_4x4_translate(mop, -1.0, -1.0, 0);
   matrix_4x4_multiply(m2, mop, m1);
   matrix_4x4_multiply(m1,
         *((math_matrix_4x4*)draw->matrix_data), m2);
   matrix_4x4_scale(mop,
         (draw->width  / 2.0) / video_info->width,
         (draw->height / 2.0) / video_info->height, 0);
   matrix_4x4_multiply(m2, mop, m1);
   matrix_4x4_translate(mop,
         (draw->x + (draw->width  / 2.0)) / video_info->width,
         (draw->y + (draw->height / 2.0)) / video_info->height,
         0);
   matrix_4x4_multiply(m1, mop, m2);
   matrix_4x4_multiply(m2, d3d->mvp_transposed, m1);
   d3d_matrix_transpose(&m1, &m2);

   d3d8_set_mvp(d3d->dev, &m1);

   if (draw && draw->texture)
      menu_display_d3d8_bind_texture(draw, d3d);

   d3d8_draw_primitive(d3d->dev,
         menu_display_prim_to_d3d8_enum(draw->prim_type),
         d3d->menu_display.offset,
         draw->coords->vertices -
         ((draw->prim_type == MENU_DISPLAY_PRIM_TRIANGLESTRIP)
          ? 2 : 0));

   d3d->menu_display.offset += draw->coords->vertices;
}