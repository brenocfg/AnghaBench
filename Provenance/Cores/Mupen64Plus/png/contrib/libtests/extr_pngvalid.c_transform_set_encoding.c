#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  chrm_mod; int /*<<< orphan*/  gama_mod; int /*<<< orphan*/  srgb_mod; TYPE_2__* pm; } ;
typedef  TYPE_1__ transform_display ;
struct TYPE_11__ {scalar_t__ current_encoding; int /*<<< orphan*/  current_gamma; } ;
typedef  TYPE_2__ png_modifier ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_sRGB_INTENT_ABSOLUTE ; 
 int /*<<< orphan*/  chrm_modification_init (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  gama_modification_init (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ modifier_color_encoding_is_sRGB (TYPE_2__*) ; 
 scalar_t__ modifier_color_encoding_is_set (TYPE_2__*) ; 
 int /*<<< orphan*/  modifier_set_encoding (TYPE_2__*) ; 
 int /*<<< orphan*/  srgb_modification_init (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
transform_set_encoding(transform_display *this)
{
   /* Set up the png_modifier '_current' fields then use these to determine how
    * to add appropriate chunks.
    */
   png_modifier *pm = this->pm;

   modifier_set_encoding(pm);

   if (modifier_color_encoding_is_set(pm))
   {
      if (modifier_color_encoding_is_sRGB(pm))
         srgb_modification_init(&this->srgb_mod, pm, PNG_sRGB_INTENT_ABSOLUTE);

      else
      {
         /* Set gAMA and cHRM separately. */
         gama_modification_init(&this->gama_mod, pm, pm->current_gamma);

         if (pm->current_encoding != 0)
            chrm_modification_init(&this->chrm_mod, pm, pm->current_encoding);
      }
   }
}