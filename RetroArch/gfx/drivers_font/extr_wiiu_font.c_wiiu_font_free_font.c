#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ image; } ;
struct TYPE_7__ {TYPE_1__ surface; } ;
struct TYPE_9__ {scalar_t__ ubo_tex; TYPE_2__ texture; scalar_t__ font_data; TYPE_3__* font_driver; } ;
typedef  TYPE_4__ wiiu_font_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* free ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MEM1_free (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void wiiu_font_free_font(void* data, bool is_threaded)
{
   wiiu_font_t* font = (wiiu_font_t*)data;

   if (!font)
      return;

   if (font->font_driver && font->font_data &&
         font->font_driver->free)
      font->font_driver->free(font->font_data);

   if (font->texture.surface.image)
      MEM1_free(font->texture.surface.image);
   if (font->ubo_tex)
      MEM1_free(font->ubo_tex);
   free(font);
}