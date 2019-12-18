#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct video_coords {int* tex_coord; int* vertex; int* color; unsigned int vertices; int* lut_tex_coord; } ;
struct font_glyph {int draw_offset_x; int draw_offset_y; int atlas_offset_x; int atlas_offset_y; int width; int height; scalar_t__ advance_y; scalar_t__ advance_x; } ;
struct TYPE_11__ {int width; int height; } ;
struct TYPE_14__ {TYPE_2__ vp; } ;
typedef  TYPE_5__ gl_core_t ;
struct TYPE_15__ {TYPE_4__* block; int /*<<< orphan*/  font_data; TYPE_3__* font_driver; TYPE_5__* gl; TYPE_1__* atlas; } ;
typedef  TYPE_6__ gl_core_raster_t ;
struct TYPE_13__ {int /*<<< orphan*/  carr; } ;
struct TYPE_12__ {struct font_glyph* (* get_glyph ) (int /*<<< orphan*/ ,char) ;} ;
struct TYPE_10__ {float width; float height; } ;
typedef  int GLfloat ;

/* Variables and functions */
 int MAX_MSG_LEN_CHUNK ; 
#define  TEXT_ALIGN_CENTER 129 
#define  TEXT_ALIGN_RIGHT 128 
 double gl_core_get_message_width (TYPE_6__*,char const*,unsigned int,int) ; 
 int /*<<< orphan*/  gl_core_raster_font_draw_vertices (TYPE_6__*,struct video_coords*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_core_raster_font_emit (int,int,int) ; 
 int roundf (int) ; 
 struct font_glyph* stub1 (int /*<<< orphan*/ ,unsigned int) ; 
 struct font_glyph* stub2 (int /*<<< orphan*/ ,char) ; 
 unsigned int utf8_walk (char const**) ; 
 int /*<<< orphan*/  video_coord_array_append (int /*<<< orphan*/ *,struct video_coords*,unsigned int) ; 

__attribute__((used)) static void gl_core_raster_font_render_line(
      gl_core_raster_t *font, const char *msg, unsigned msg_len,
      GLfloat scale, const GLfloat color[4], GLfloat pos_x,
      GLfloat pos_y, unsigned text_align,
      video_frame_info_t *video_info)
{
   unsigned i;
   struct video_coords coords;
   GLfloat font_tex_coords[2 * 6 * MAX_MSG_LEN_CHUNK];
   GLfloat font_vertex[2 * 6 * MAX_MSG_LEN_CHUNK];
   GLfloat font_color[4 * 6 * MAX_MSG_LEN_CHUNK];
   gl_core_t *gl        = font->gl;
   const char* msg_end  = msg + msg_len;
   int x                = roundf(pos_x * gl->vp.width);
   int y                = roundf(pos_y * gl->vp.height);
   int delta_x          = 0;
   int delta_y          = 0;
   float inv_tex_size_x = 1.0f / font->atlas->width;
   float inv_tex_size_y = 1.0f / font->atlas->height;
   float inv_win_width  = 1.0f / font->gl->vp.width;
   float inv_win_height = 1.0f / font->gl->vp.height;

   switch (text_align)
   {
      case TEXT_ALIGN_RIGHT:
         x -= gl_core_get_message_width(font, msg, msg_len, scale);
         break;
      case TEXT_ALIGN_CENTER:
         x -= gl_core_get_message_width(font, msg, msg_len, scale) / 2.0;
         break;
   }

   while (msg < msg_end)
   {
      i = 0;
      while ((i < MAX_MSG_LEN_CHUNK) && (msg < msg_end))
      {
         int off_x, off_y, tex_x, tex_y, width, height;
         unsigned                  code = utf8_walk(&msg);
         const struct font_glyph *glyph = font->font_driver->get_glyph(
               font->font_data, code);

         if (!glyph) /* Do something smarter here ... */
            glyph = font->font_driver->get_glyph(font->font_data, '?');

         if (!glyph)
            continue;

         off_x  = glyph->draw_offset_x;
         off_y  = glyph->draw_offset_y;
         tex_x  = glyph->atlas_offset_x;
         tex_y  = glyph->atlas_offset_y;
         width  = glyph->width;
         height = glyph->height;

         gl_core_raster_font_emit(0, 0, 1); /* Bottom-left */
         gl_core_raster_font_emit(1, 1, 1); /* Bottom-right */
         gl_core_raster_font_emit(2, 0, 0); /* Top-left */

         gl_core_raster_font_emit(3, 1, 0); /* Top-right */
         gl_core_raster_font_emit(4, 0, 0); /* Top-left */
         gl_core_raster_font_emit(5, 1, 1); /* Bottom-right */

         i++;

         delta_x += glyph->advance_x;
         delta_y -= glyph->advance_y;
      }

      coords.tex_coord     = font_tex_coords;
      coords.vertex        = font_vertex;
      coords.color         = font_color;
      coords.vertices      = i * 6;
      coords.lut_tex_coord = font_tex_coords;

      if (font->block)
         video_coord_array_append(&font->block->carr, &coords, coords.vertices);
      else
         gl_core_raster_font_draw_vertices(font, &coords, video_info);
   }
}