#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct font_glyph {int dummy; } ;
struct TYPE_2__ {struct font_glyph const* glyphs; } ;
typedef  TYPE_1__ bm_renderer_t ;

/* Variables and functions */
 size_t BMP_ATLAS_SIZE ; 

__attribute__((used)) static const struct font_glyph *font_renderer_bmp_get_glyph(
      void *data, uint32_t code)
{
   bm_renderer_t *handle = (bm_renderer_t*)data;
   if (!handle)
      return NULL;
   return code < BMP_ATLAS_SIZE ? &handle->glyphs[code] : NULL;
}