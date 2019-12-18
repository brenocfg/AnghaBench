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
typedef  int uint32_t ;
struct font_glyph {int dummy; } ;
struct TYPE_2__ {struct font_glyph const* glyphs; } ;
typedef  TYPE_1__ stb_font_renderer_t ;

/* Variables and functions */

__attribute__((used)) static const struct font_glyph *font_renderer_stb_get_glyph(
      void *data, uint32_t code)
{
   stb_font_renderer_t *self = (stb_font_renderer_t*)data;
   return code < 256 ? &self->glyphs[code] : NULL;
}