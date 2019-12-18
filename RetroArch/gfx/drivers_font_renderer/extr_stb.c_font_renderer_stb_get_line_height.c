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
struct TYPE_2__ {int line_height; } ;
typedef  TYPE_1__ stb_font_renderer_t ;

/* Variables and functions */

__attribute__((used)) static int font_renderer_stb_get_line_height(void* data)
{
   stb_font_renderer_t *handle = (stb_font_renderer_t*)data;
   return handle->line_height;
}