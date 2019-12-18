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
typedef  enum rotation { ____Placeholder_rotation } rotation ;
typedef  int /*<<< orphan*/  dm ;
struct TYPE_4__ {int dmPelsWidth; int dmPelsHeight; int /*<<< orphan*/  dmDisplayOrientation; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ DEVMODE ;

/* Variables and functions */
 int /*<<< orphan*/  DMDO_180 ; 
 int /*<<< orphan*/  DMDO_270 ; 
 int /*<<< orphan*/  DMDO_90 ; 
 int /*<<< orphan*/  DMDO_DEFAULT ; 
#define  ORIENTATION_FLIPPED 131 
#define  ORIENTATION_FLIPPED_ROTATED 130 
#define  ORIENTATION_NORMAL 129 
#define  ORIENTATION_VERTICAL 128 
 int /*<<< orphan*/  win32_change_display_settings (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win32_get_video_output (TYPE_1__*,int,int) ; 

void win32_display_server_set_screen_orientation(enum rotation rotation)
{
   DEVMODE dm = {0};

   win32_get_video_output(&dm, -1, sizeof(dm));

   switch (rotation)
   {
      case ORIENTATION_NORMAL:
      default:
      {
         int width = dm.dmPelsWidth;

         if ((dm.dmDisplayOrientation == DMDO_90 || dm.dmDisplayOrientation == DMDO_270) && width != dm.dmPelsHeight)
         {
            /* device is changing orientations, swap the aspect */
            dm.dmPelsWidth = dm.dmPelsHeight;
            dm.dmPelsHeight = width;
         }

         dm.dmDisplayOrientation = DMDO_DEFAULT;
         break;
      }
      case ORIENTATION_VERTICAL:
      {
         int width = dm.dmPelsWidth;

         if ((dm.dmDisplayOrientation == DMDO_DEFAULT || dm.dmDisplayOrientation == DMDO_180) && width != dm.dmPelsHeight)
         {
            /* device is changing orientations, swap the aspect */
            dm.dmPelsWidth = dm.dmPelsHeight;
            dm.dmPelsHeight = width;
         }

         dm.dmDisplayOrientation = DMDO_270;
         break;
      }
      case ORIENTATION_FLIPPED:
      {
         int width = dm.dmPelsWidth;

         if ((dm.dmDisplayOrientation == DMDO_90 || dm.dmDisplayOrientation == DMDO_270) && width != dm.dmPelsHeight)
         {
            /* device is changing orientations, swap the aspect */
            dm.dmPelsWidth = dm.dmPelsHeight;
            dm.dmPelsHeight = width;
         }

         dm.dmDisplayOrientation = DMDO_180;
         break;
      }
      case ORIENTATION_FLIPPED_ROTATED:
      {
         int width = dm.dmPelsWidth;

         if ((dm.dmDisplayOrientation == DMDO_DEFAULT || dm.dmDisplayOrientation == DMDO_180) && width != dm.dmPelsHeight)
         {
            /* device is changing orientations, swap the aspect */
            dm.dmPelsWidth = dm.dmPelsHeight;
            dm.dmPelsHeight = width;
         }

         dm.dmDisplayOrientation = DMDO_90;
         break;
      }
   }

   win32_change_display_settings(NULL, &dm, 0);
}