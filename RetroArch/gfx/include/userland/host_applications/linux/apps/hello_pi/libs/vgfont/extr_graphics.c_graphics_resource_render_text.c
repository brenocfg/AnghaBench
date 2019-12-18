#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  GRAPHICS_RESOURCE_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ATEXT_FONT_SIZE ; 
 int /*<<< orphan*/  graphics_resource_render_text_ext (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,char const*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

int32_t graphics_resource_render_text(  GRAPHICS_RESOURCE_HANDLE res,
                                        const int32_t x,
                                        const int32_t y,
                                        const uint32_t width, /* this can be GRAPHICS_RESOURCE_WIDTH for no clipping */
                                        const uint32_t height, /* this can be GRAPHICS_RESOURCE_HEIGHT for no clipping */
                                        const uint32_t fg_colour,
                                        const uint32_t bg_colour,
                                        const char *text,
                                        const uint32_t text_length)
{
   return graphics_resource_render_text_ext(res, x, y, width, height,
                                            fg_colour, bg_colour,
                                            text, text_length,
                                            ATEXT_FONT_SIZE);
}