#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ font; } ;
typedef  TYPE_1__ d3dfonts_t ;

/* Variables and functions */
 int /*<<< orphan*/  d3d9x_font_release (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void d3dfonts_w32_free_font(void *data, bool is_threaded)
{
   d3dfonts_t *d3dfonts = (d3dfonts_t*)data;

   if (!d3dfonts)
      return;

   if (d3dfonts->font)
      d3d9x_font_release(d3dfonts->font);

   free(d3dfonts);
}