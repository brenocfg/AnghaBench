#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_20__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_18__ ;
typedef  struct TYPE_26__   TYPE_14__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
struct TYPE_32__ {unsigned int current; unsigned int size; TYPE_14__* v; } ;
struct TYPE_23__ {TYPE_4__ vertex_cache; int /*<<< orphan*/  ubo_tex; } ;
typedef  TYPE_11__ wiiu_video_t ;
struct TYPE_33__ {unsigned int height; unsigned int pitch; int imageSize; TYPE_14__* image; } ;
struct TYPE_29__ {TYPE_5__ surface; } ;
struct TYPE_24__ {int /*<<< orphan*/  ubo_tex; TYPE_20__ texture; TYPE_6__* atlas; int /*<<< orphan*/  font_data; TYPE_1__* font_driver; } ;
typedef  TYPE_12__ wiiu_font_t ;
struct TYPE_25__ {unsigned int width; unsigned int height; scalar_t__ userdata; } ;
typedef  TYPE_13__ video_frame_info_t ;
struct font_glyph {float draw_offset_x; float draw_offset_y; float width; float height; float advance_x; float advance_y; int /*<<< orphan*/  atlas_offset_y; int /*<<< orphan*/  atlas_offset_x; } ;
struct TYPE_31__ {float width; float height; int /*<<< orphan*/  v; int /*<<< orphan*/  u; } ;
struct TYPE_30__ {int x; int y; float width; float height; } ;
struct TYPE_26__ {unsigned int color; TYPE_3__ coord; TYPE_2__ pos; } ;
typedef  TYPE_14__ sprite_vertex_t ;
struct TYPE_37__ {TYPE_10__* uniformBlocks; } ;
struct TYPE_36__ {TYPE_7__* samplerVars; } ;
struct TYPE_35__ {int /*<<< orphan*/  location; } ;
struct TYPE_34__ {int dirty; unsigned int height; unsigned int width; scalar_t__ buffer; } ;
struct TYPE_28__ {struct font_glyph* (* get_glyph ) (int /*<<< orphan*/ ,char) ;} ;
struct TYPE_27__ {TYPE_9__ vs; TYPE_8__ ps; } ;
struct TYPE_22__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX2DrawEx (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  GX2Invalidate (int /*<<< orphan*/ ,TYPE_14__*,int) ; 
 int /*<<< orphan*/  GX2SetPixelTexture (TYPE_20__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX2SetVertexUniformBlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX2_INVALIDATE_MODE_CPU_ATTRIBUTE_BUFFER ; 
 int /*<<< orphan*/  GX2_INVALIDATE_MODE_CPU_TEXTURE ; 
 int /*<<< orphan*/  GX2_PRIMITIVE_MODE_POINTS ; 
#define  TEXT_ALIGN_CENTER 129 
#define  TEXT_ALIGN_RIGHT 128 
 int /*<<< orphan*/  memcpy (TYPE_14__*,scalar_t__,unsigned int) ; 
 int roundf (double) ; 
 TYPE_18__ sprite_shader ; 
 struct font_glyph* stub1 (int /*<<< orphan*/ ,unsigned int) ; 
 struct font_glyph* stub2 (int /*<<< orphan*/ ,char) ; 
 unsigned int utf8_walk (char const**) ; 
 int wiiu_font_get_message_width (TYPE_12__*,char const*,unsigned int,float) ; 

__attribute__((used)) static void wiiu_font_render_line(
      video_frame_info_t *video_info,
      wiiu_font_t* font, const char* msg, unsigned msg_len,
      float scale, const unsigned int color, float pos_x,
      float pos_y, unsigned text_align)
{
   unsigned i;
   wiiu_video_t* wiiu = (wiiu_video_t*)video_info->userdata;
   unsigned width   = video_info->width;
   unsigned height  = video_info->height;
   int x            = roundf(pos_x * width);
   int y            = roundf((1.0 - pos_y) * height);

   if(  !wiiu ||
         wiiu->vertex_cache.current + (msg_len * 4) > wiiu->vertex_cache.size)
      return;

   switch (text_align)
   {
      case TEXT_ALIGN_RIGHT:
         x -= wiiu_font_get_message_width(font, msg, msg_len, scale);
         break;

      case TEXT_ALIGN_CENTER:
         x -= wiiu_font_get_message_width(font, msg, msg_len, scale) / 2;
         break;
   }

   sprite_vertex_t* v = wiiu->vertex_cache.v + wiiu->vertex_cache.current;

   for (i = 0; i < msg_len; i++)
   {
      const char* msg_tmp            = &msg[i];
      unsigned code                  = utf8_walk(&msg_tmp);
      unsigned skip                  = msg_tmp - &msg[i];

      if (skip > 1)
         i += skip - 1;

      const struct font_glyph* glyph =
         font->font_driver->get_glyph(font->font_data, code);

      if (!glyph) /* Do something smarter here ... */
         glyph = font->font_driver->get_glyph(font->font_data, '?');

      if (!glyph)
         continue;

      v->pos.x = x + glyph->draw_offset_x * scale;
      v->pos.y = y + glyph->draw_offset_y * scale;
      v->pos.width = glyph->width * scale;
      v->pos.height = glyph->height * scale;

      v->coord.u = glyph->atlas_offset_x;
      v->coord.v = glyph->atlas_offset_y;
      v->coord.width = glyph->width;
      v->coord.height = glyph->height;

      v->color = color;

      v++;

      x += glyph->advance_x * scale;
      y += glyph->advance_y * scale;
   }

   int count = v - wiiu->vertex_cache.v - wiiu->vertex_cache.current;

   if (!count)
      return;

   GX2Invalidate(GX2_INVALIDATE_MODE_CPU_ATTRIBUTE_BUFFER, wiiu->vertex_cache.v + wiiu->vertex_cache.current, count * sizeof(wiiu->vertex_cache.v));

   if(font->atlas->dirty)
   {
      for (i = 0; (i < font->atlas->height) && (i < font->texture.surface.height); i++)
         memcpy(font->texture.surface.image + (i * font->texture.surface.pitch),
                font->atlas->buffer + (i * font->atlas->width), font->atlas->width);

      GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, font->texture.surface.image,
                    font->texture.surface.imageSize);
      font->atlas->dirty = false;
   }

   GX2SetPixelTexture(&font->texture, sprite_shader.ps.samplerVars[0].location);
   GX2SetVertexUniformBlock(sprite_shader.vs.uniformBlocks[1].offset, sprite_shader.vs.uniformBlocks[1].size, font->ubo_tex);

   GX2DrawEx(GX2_PRIMITIVE_MODE_POINTS, count, wiiu->vertex_cache.current, 1);

   GX2SetVertexUniformBlock(sprite_shader.vs.uniformBlocks[1].offset, sprite_shader.vs.uniformBlocks[1].size, wiiu->ubo_tex);

   wiiu->vertex_cache.current = v - wiiu->vertex_cache.v;
}