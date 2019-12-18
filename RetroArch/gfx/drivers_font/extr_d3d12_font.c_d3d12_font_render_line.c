#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_16__ ;
typedef  struct TYPE_29__   TYPE_15__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {unsigned int width; unsigned int height; scalar_t__ userdata; } ;
typedef  TYPE_11__ video_frame_info_t ;
struct font_glyph {float draw_offset_x; float draw_offset_y; float width; float height; float atlas_offset_x; float atlas_offset_y; float advance_x; float advance_y; } ;
struct TYPE_36__ {unsigned int offset; int /*<<< orphan*/  pipe; int /*<<< orphan*/  pipe_font; int /*<<< orphan*/  vbo; scalar_t__ capacity; int /*<<< orphan*/  enabled; } ;
struct TYPE_35__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_38__ {scalar_t__ Height; scalar_t__ Width; } ;
struct TYPE_39__ {TYPE_8__ viewport; } ;
struct TYPE_26__ {TYPE_6__ sprites; TYPE_5__ queue; TYPE_9__ chain; } ;
typedef  TYPE_12__ d3d12_video_t ;
struct TYPE_33__ {int scaling; scalar_t__ rotation; } ;
struct TYPE_31__ {float u; float v; float w; float h; } ;
struct TYPE_24__ {int x; int y; float w; float h; } ;
struct TYPE_27__ {unsigned int* colors; TYPE_3__ params; TYPE_1__ coords; TYPE_10__ pos; } ;
typedef  TYPE_13__ d3d12_sprite_t ;
struct TYPE_32__ {scalar_t__ Height; scalar_t__ Width; } ;
struct TYPE_30__ {scalar_t__ dirty; TYPE_2__ desc; } ;
struct TYPE_28__ {TYPE_16__ texture; TYPE_4__* atlas; int /*<<< orphan*/  font_data; TYPE_7__* font_driver; } ;
typedef  TYPE_14__ d3d12_font_t ;
struct TYPE_37__ {struct font_glyph* (* get_glyph ) (int /*<<< orphan*/ ,char) ;} ;
struct TYPE_34__ {int dirty; int /*<<< orphan*/  buffer; int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct TYPE_29__ {uintptr_t Begin; uintptr_t End; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_15__ D3D12_RANGE ;

/* Variables and functions */
 int /*<<< orphan*/  D3D12DrawInstanced (int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3D12Map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_15__*,void**) ; 
 int /*<<< orphan*/  D3D12SetPipelineState (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3D12Unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_15__*) ; 
 int /*<<< orphan*/  DXGI_FORMAT_A8_UNORM ; 
#define  TEXT_ALIGN_CENTER 129 
#define  TEXT_ALIGN_RIGHT 128 
 int d3d12_font_get_message_width (TYPE_14__*,char const*,unsigned int,float) ; 
 int /*<<< orphan*/  d3d12_set_texture_and_sampler (int /*<<< orphan*/ ,TYPE_16__*) ; 
 int /*<<< orphan*/  d3d12_update_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_16__*) ; 
 int /*<<< orphan*/  d3d12_upload_texture (int /*<<< orphan*/ ,TYPE_16__*,scalar_t__) ; 
 int roundf (double) ; 
 struct font_glyph* stub1 (int /*<<< orphan*/ ,unsigned int) ; 
 struct font_glyph* stub2 (int /*<<< orphan*/ ,char) ; 
 unsigned int utf8_walk (char const**) ; 

__attribute__((used)) static void d3d12_font_render_line(
      video_frame_info_t* video_info,
      d3d12_font_t*       font,
      const char*         msg,
      unsigned            msg_len,
      float               scale,
      const unsigned int  color,
      float               pos_x,
      float               pos_y,
      unsigned            text_align)
{
   unsigned        i, count;
   void*           mapped_vbo = NULL;
   d3d12_sprite_t* v          = NULL;
   d3d12_sprite_t* vbo_start  = NULL;
   d3d12_video_t*  d3d12      = (d3d12_video_t*)video_info->userdata;
   unsigned        width      = video_info->width;
   unsigned        height     = video_info->height;
   int             x          = roundf(pos_x * width);
   int             y          = roundf((1.0 - pos_y) * height);
   D3D12_RANGE     range      = { 0, 0 };

   if (  !d3d12                  ||
         !d3d12->sprites.enabled ||
         msg_len > (unsigned)d3d12->sprites.capacity)
      return;

   if (d3d12->sprites.offset + msg_len > (unsigned)d3d12->sprites.capacity)
      d3d12->sprites.offset = 0;

   switch (text_align)
   {
      case TEXT_ALIGN_RIGHT:
         x -= d3d12_font_get_message_width(font, msg, msg_len, scale);
         break;

      case TEXT_ALIGN_CENTER:
         x -= d3d12_font_get_message_width(font, msg, msg_len, scale) / 2;
         break;
   }

   D3D12Map(d3d12->sprites.vbo, 0, &range, (void**)&vbo_start);

   v           = vbo_start + d3d12->sprites.offset;
   range.Begin = (uintptr_t)v - (uintptr_t)vbo_start;

   for (i = 0; i < msg_len; i++)
   {
      const struct font_glyph* glyph;
      const char*              msg_tmp = &msg[i];
      unsigned                 code    = utf8_walk(&msg_tmp);
      unsigned                 skip    = msg_tmp - &msg[i];

      if (skip > 1)
         i += skip - 1;

      glyph = font->font_driver->get_glyph(font->font_data, code);

      if (!glyph) /* Do something smarter here ... */
         glyph = font->font_driver->get_glyph(font->font_data, '?');

      if (!glyph)
         continue;

      v->pos.x = (x + (glyph->draw_offset_x * scale)) / (float)d3d12->chain.viewport.Width;
      v->pos.y = (y + (glyph->draw_offset_y * scale)) / (float)d3d12->chain.viewport.Height;
      v->pos.w = glyph->width * scale  / (float)d3d12->chain.viewport.Width;
      v->pos.h = glyph->height * scale / (float)d3d12->chain.viewport.Height;

      v->coords.u = glyph->atlas_offset_x / (float)font->texture.desc.Width;
      v->coords.v = glyph->atlas_offset_y / (float)font->texture.desc.Height;
      v->coords.w = glyph->width          / (float)font->texture.desc.Width;
      v->coords.h = glyph->height         / (float)font->texture.desc.Height;

      v->params.scaling  = 1;
      v->params.rotation = 0;

      v->colors[0] = color;
      v->colors[1] = color;
      v->colors[2] = color;
      v->colors[3] = color;

      v++;

      x += glyph->advance_x * scale;
      y += glyph->advance_y * scale;
   }

   range.End = (uintptr_t)v - (uintptr_t)vbo_start;
   D3D12Unmap(d3d12->sprites.vbo, 0, &range);

   count = v - vbo_start - d3d12->sprites.offset;

   if (!count)
      return;

   if (font->atlas->dirty)
   {
      d3d12_update_texture(
            font->atlas->width, font->atlas->height,
            font->atlas->width, DXGI_FORMAT_A8_UNORM,
            font->atlas->buffer, &font->texture);
      font->atlas->dirty = false;
   }

   if(font->texture.dirty)
      d3d12_upload_texture(d3d12->queue.cmd, &font->texture,
            video_info->userdata);

   D3D12SetPipelineState(d3d12->queue.cmd, d3d12->sprites.pipe_font);
   d3d12_set_texture_and_sampler(d3d12->queue.cmd, &font->texture);
   D3D12DrawInstanced(d3d12->queue.cmd, count, 1, d3d12->sprites.offset, 0);

   D3D12SetPipelineState(d3d12->queue.cmd, d3d12->sprites.pipe);

   d3d12->sprites.offset += count;
}