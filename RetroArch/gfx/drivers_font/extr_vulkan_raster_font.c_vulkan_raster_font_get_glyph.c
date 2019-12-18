#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* font_driver; } ;
typedef  TYPE_2__ vulkan_raster_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct font_glyph {int dummy; } ;
struct TYPE_4__ {struct font_glyph* (* get_glyph ) (void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 struct font_glyph* stub1 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vulkan_raster_font_update_glyph (TYPE_2__*,struct font_glyph const*) ; 

__attribute__((used)) static const struct font_glyph *vulkan_raster_font_get_glyph(
      void *data, uint32_t code)
{
   const struct font_glyph* glyph;
   vulkan_raster_t *font = (vulkan_raster_t*)data;

   if (!font || !font->font_driver)
      return NULL;
   if (!font->font_driver->ident)
       return NULL;

   glyph = font->font_driver->get_glyph((void*)font->font_driver, code);

   if(glyph)
      vulkan_raster_font_update_glyph(font, glyph);

   return glyph;
}