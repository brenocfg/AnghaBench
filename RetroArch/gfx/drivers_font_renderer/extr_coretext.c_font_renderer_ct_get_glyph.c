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
typedef  size_t uint32_t ;
struct font_glyph {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * atlas_slots; } ;
typedef  TYPE_1__ ct_font_renderer_t ;
struct TYPE_4__ {struct font_glyph const glyph; } ;
typedef  TYPE_2__ coretext_atlas_slot_t ;

/* Variables and functions */
 size_t CT_ATLAS_SIZE ; 

__attribute__((used)) static const struct font_glyph *font_renderer_ct_get_glyph(
    void *data, uint32_t charcode)
{
   coretext_atlas_slot_t *atlas_slot = NULL;
   ct_font_renderer_t        *handle = (ct_font_renderer_t*)data;

   if (!handle || charcode >= CT_ATLAS_SIZE)
      return NULL;

   atlas_slot = (coretext_atlas_slot_t*)&handle->atlas_slots[charcode];

   return &atlas_slot->glyph;
}