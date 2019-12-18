#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct font_glyph {scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  draw_offset_y; int /*<<< orphan*/  draw_offset_x; scalar_t__ atlas_offset_y; scalar_t__ atlas_offset_x; int /*<<< orphan*/  advance_x; } ;
struct TYPE_11__ {scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; int /*<<< orphan*/  yoff; int /*<<< orphan*/  xoff; int /*<<< orphan*/  xadvance; } ;
typedef  TYPE_2__ stbtt_packedchar ;
struct TYPE_12__ {int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_3__ stbtt_pack_context ;
struct TYPE_10__ {unsigned int width; unsigned int height; int dirty; int /*<<< orphan*/ * buffer; } ;
struct TYPE_13__ {TYPE_1__ atlas; struct font_glyph* glyphs; } ;
typedef  TYPE_4__ stb_font_renderer_t ;

/* Variables and functions */
 int MIN (int,int) ; 
 int /*<<< orphan*/  RARCH_WARN (char*,unsigned int,unsigned int) ; 
 scalar_t__ calloc (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ isalnum (int) ; 
 int /*<<< orphan*/  stbtt_PackBegin (TYPE_3__*,int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stbtt_PackEnd (TYPE_3__*) ; 
 int /*<<< orphan*/  stbtt_PackFontRange (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int,TYPE_2__*) ; 

__attribute__((used)) static bool font_renderer_stb_create_atlas(stb_font_renderer_t *self,
      uint8_t *font_data, float font_size, unsigned width, unsigned height)
{
   int i;
   stbtt_packedchar   chardata[256];
   stbtt_pack_context pc = {NULL};

   if (width > 2048 || height > 2048)
   {
      RARCH_WARN("[stb] Font atlas too big: %ux%u\n", width, height);
      goto error;
   }

   if (self->atlas.buffer)
      free(self->atlas.buffer);

   self->atlas.buffer = (uint8_t*)calloc(height, width);
   self->atlas.width  = width;
   self->atlas.height = height;

   if (!self->atlas.buffer)
      goto error;

   stbtt_PackBegin(&pc, self->atlas.buffer,
         self->atlas.width, self->atlas.height,
         self->atlas.width, 1, NULL);

   stbtt_PackFontRange(&pc, font_data, 0, font_size, 0, 256, chardata);
   stbtt_PackEnd(&pc);

   self->atlas.dirty = true;

   for (i = 0; i < 256; ++i)
   {
      struct font_glyph *g = &self->glyphs[i];
      stbtt_packedchar  *c = &chardata[i];

      g->advance_x         = c->xadvance;
      g->atlas_offset_x    = c->x0;
      g->atlas_offset_y    = c->y0;
      g->draw_offset_x     = c->xoff;
      g->draw_offset_y     = c->yoff;
      g->width             = c->x1 - c->x0;
      g->height            = c->y1 - c->y0;

      /* Make sure important characters fit */
      if (isalnum(i) && (!g->width || !g->height))
      {
         int new_width  = width  * 1.2;
         int new_height = height * 1.2;

         /* Limit growth to 2048x2048 unless we already reached that */
         if (width < 2048 || height < 2048)
         {
            new_width  = MIN(new_width,  2048);
            new_height = MIN(new_height, 2048);
         }

         return font_renderer_stb_create_atlas(self, font_data, font_size,
               new_width, new_height);
      }
   }

   return true;

error:
   self->atlas.width = self->atlas.height = 0;

   if (self->atlas.buffer)
      free(self->atlas.buffer);

   self->atlas.buffer = NULL;

   return false;
}