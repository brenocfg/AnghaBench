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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int int32_t ;
struct TYPE_3__ {int width; int height; } ;
typedef  TYPE_1__ DISPMANX_MODEINFO_T ;
typedef  int /*<<< orphan*/  DISPMANX_DISPLAY_HANDLE_T ;

/* Variables and functions */
 scalar_t__ const MAX_DISPLAY_HANDLES ; 
 scalar_t__ gx_priv_open_screen (scalar_t__ const,int /*<<< orphan*/ *) ; 
 int vc_dispmanx_display_get_info (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 scalar_t__ vcos_verify (int) ; 

int32_t graphics_get_display_size( const uint16_t display_number,
                                   uint32_t *width,
                                   uint32_t *height)
{
   DISPMANX_MODEINFO_T mode_info;
   int32_t success = -1;
   DISPMANX_DISPLAY_HANDLE_T disp;
   vcos_assert(width && height);
   *width = *height = 0;

   if(vcos_verify(display_number < MAX_DISPLAY_HANDLES))
   {
      // TODO Shouldn't this close the display if it wasn't previously open?
      if (gx_priv_open_screen(display_number, &disp) < 0)
      {
         vcos_assert(0);
         return -1;
      }
      success = vc_dispmanx_display_get_info(disp, &mode_info);

      if( success >= 0 )
      {
         *width = mode_info.width;
         *height = mode_info.height;
         vcos_assert(*height > 64);
      }
      else
      {
         vcos_assert(0);
      }
   }

   return success;
}