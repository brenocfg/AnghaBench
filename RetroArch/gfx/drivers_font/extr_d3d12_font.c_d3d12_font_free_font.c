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
struct TYPE_5__ {int /*<<< orphan*/  texture; scalar_t__ font_data; TYPE_1__* font_driver; } ;
typedef  TYPE_2__ d3d12_font_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* free ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  d3d12_release_texture (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void d3d12_font_free_font(void* data, bool is_threaded)
{
   d3d12_font_t* font = (d3d12_font_t*)data;

   if (!font)
      return;

   if (font->font_driver && font->font_data && font->font_driver->free)
      font->font_driver->free(font->font_data);

   d3d12_release_texture(&font->texture);

   free(font);
}