#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {TYPE_2__ texture; scalar_t__ font_data; TYPE_1__* font_driver; } ;
typedef  TYPE_3__ ctr_font_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* free ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  linearFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  vramFree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ctr_font_free_font(void* data, bool is_threaded)
{
   ctr_font_t* font = (ctr_font_t*)data;

   if (!font)
      return;

   if (font->font_driver && font->font_data)
      font->font_driver->free(font->font_data);

#ifdef FONT_TEXTURE_IN_VRAM
   vramFree(font->texture.data);
#else
   linearFree(font->texture.data);
#endif
   free(font);
}