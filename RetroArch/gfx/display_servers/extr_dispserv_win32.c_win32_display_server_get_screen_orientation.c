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
typedef  enum rotation { ____Placeholder_rotation } rotation ;
typedef  int /*<<< orphan*/  dm ;
struct TYPE_3__ {int dmDisplayOrientation; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ DEVMODE ;

/* Variables and functions */
#define  DMDO_180 131 
#define  DMDO_270 130 
#define  DMDO_90 129 
#define  DMDO_DEFAULT 128 
 int ORIENTATION_FLIPPED ; 
 int ORIENTATION_FLIPPED_ROTATED ; 
 int ORIENTATION_NORMAL ; 
 int ORIENTATION_VERTICAL ; 
 int /*<<< orphan*/  win32_get_video_output (TYPE_1__*,int,int) ; 

enum rotation win32_display_server_get_screen_orientation(void)
{
   DEVMODE dm = {0};
   enum rotation rotation;

   win32_get_video_output(&dm, -1, sizeof(dm));

   switch (dm.dmDisplayOrientation)
   {
      case DMDO_DEFAULT:
      default:
         rotation = ORIENTATION_NORMAL;
         break;
      case DMDO_90:
         rotation = ORIENTATION_FLIPPED_ROTATED;
         break;
      case DMDO_180:
         rotation = ORIENTATION_FLIPPED;
         break;
      case DMDO_270:
         rotation = ORIENTATION_VERTICAL;
         break;
   }

   return rotation;
}