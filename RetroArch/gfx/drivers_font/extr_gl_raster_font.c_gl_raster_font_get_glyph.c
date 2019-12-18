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
typedef  int /*<<< orphan*/  uint32_t ;
struct font_glyph {int dummy; } ;
struct TYPE_4__ {TYPE_1__* font_driver; } ;
typedef  TYPE_2__ gl_raster_t ;
struct TYPE_3__ {struct font_glyph const* (* get_glyph ) (void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 struct font_glyph const* stub1 (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct font_glyph *gl_raster_font_get_glyph(
      void *data, uint32_t code)
{
   gl_raster_t *font = (gl_raster_t*)data;

   if (!font || !font->font_driver)
      return NULL;
   if (!font->font_driver->ident)
       return NULL;
   return font->font_driver->get_glyph((void*)font->font_driver, code);
}