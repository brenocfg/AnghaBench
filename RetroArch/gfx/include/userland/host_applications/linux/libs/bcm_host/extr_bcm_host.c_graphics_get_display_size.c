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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ DISPMANX_MODEINFO_T ;
typedef  scalar_t__ DISPMANX_DISPLAY_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  vc_dispmanx_display_close (scalar_t__) ; 
 int vc_dispmanx_display_get_info (scalar_t__,TYPE_1__*) ; 
 scalar_t__ vc_dispmanx_display_open (int /*<<< orphan*/  const) ; 

int32_t graphics_get_display_size( const uint16_t display_number,
                                                    uint32_t *width,
                                                    uint32_t *height)
{
   DISPMANX_DISPLAY_HANDLE_T display_handle = 0;
   DISPMANX_MODEINFO_T mode_info;
   int32_t success = -1;

   // Display must be opened first.
   display_handle = vc_dispmanx_display_open(display_number);

   if (display_handle) {
      success = vc_dispmanx_display_get_info(display_handle, &mode_info);

      if( success >= 0 )
      {
         if( NULL != width )
         {
            *width = mode_info.width;
         }

         if( NULL != height )
         {
            *height = mode_info.height;
         }
      }
      vc_dispmanx_display_close(display_handle);
      display_handle = 0;
   }

   return success;
}