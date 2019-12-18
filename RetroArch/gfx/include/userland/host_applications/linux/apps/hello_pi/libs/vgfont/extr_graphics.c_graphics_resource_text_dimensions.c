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
 int /*<<< orphan*/  graphics_resource_text_dimensions_ext (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int32_t graphics_resource_text_dimensions( GRAPHICS_RESOURCE_HANDLE resource_handle,
                                           const char *text,
                                           const uint32_t text_length,
                                           uint32_t *width,
                                           uint32_t *height )
{
   return graphics_resource_text_dimensions_ext(resource_handle, text, text_length, width, height, ATEXT_FONT_SIZE);
}