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
struct TYPE_2__ {unsigned int width; unsigned int height; } ;
typedef  TYPE_1__ gfx_ctx_osmesa_data_t ;

/* Variables and functions */

__attribute__((used)) static void osmesa_ctx_check_window(void *data, bool *quit,
      bool *resize,unsigned *width,
      unsigned *height, bool is_shutdown)
{
   gfx_ctx_osmesa_data_t *osmesa = (gfx_ctx_osmesa_data_t*)data;

   *width              = osmesa->width;
   *height             = osmesa->height;
   *resize             = false;
   *quit               = false;
}