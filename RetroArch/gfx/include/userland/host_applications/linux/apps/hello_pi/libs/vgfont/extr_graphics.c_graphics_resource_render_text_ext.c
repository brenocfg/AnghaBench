#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  scalar_t__ VCOS_STATUS_T ;
struct TYPE_4__ {int const height; } ;
typedef  TYPE_1__* GRAPHICS_RESOURCE_HANDLE ;

/* Variables and functions */
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  display ; 
 scalar_t__ gx_priv_render_text (int /*<<< orphan*/ *,TYPE_1__*,int const,int const,int const,int const,int const,int const,char const*,int const,int const) ; 

int32_t graphics_resource_render_text_ext( GRAPHICS_RESOURCE_HANDLE res,
                                           const int32_t x,
                                           const int32_t y,
                                           const uint32_t width,
                                           const uint32_t height,
                                           const uint32_t fg_colour,
                                           const uint32_t bg_colour,
                                           const char *text,
                                           const uint32_t text_length,
                                           const uint32_t text_size )
{

   /*
   * FIXME: Not at all optimal - re-renders each time.
   * FIXME: Not UTF-8 safe
   * FIXME: much better caching (or any caching)
   */
   VCOS_STATUS_T rc = gx_priv_render_text(
      &display, res,
      x, res->height-y-text_size, width, height, fg_colour, bg_colour,
      text, text_length, text_size);

   return (rc == VCOS_SUCCESS) ? 0 : -1;
}