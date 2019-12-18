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
typedef  int /*<<< orphan*/  dispserv_win32_t ;
typedef  int /*<<< orphan*/  devmode ;
typedef  int /*<<< orphan*/  curDevmode ;
struct TYPE_4__ {int dmDisplayFrequency; unsigned int dmPelsWidth; unsigned int dmPelsHeight; int dmBitsPerPel; int dmFields; } ;
typedef  int LONG ;
typedef  TYPE_1__ DEVMODE ;

/* Variables and functions */
 int /*<<< orphan*/  CDS_TEST ; 
#define  DISP_CHANGE_NOTUPDATED 130 
#define  DISP_CHANGE_RESTART 129 
#define  DISP_CHANGE_SUCCESSFUL 128 
 int DM_BITSPERPEL ; 
 int DM_DISPLAYFREQUENCY ; 
 int DM_PELSHEIGHT ; 
 int DM_PELSWIDTH ; 
 scalar_t__ GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXSCREEN ; 
 int /*<<< orphan*/  SM_CYSCREEN ; 
 int win32_change_display_settings (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win32_get_video_output (TYPE_1__*,int,int) ; 
 scalar_t__ win32_orig_height ; 
 int win32_orig_refresh ; 
 scalar_t__ win32_orig_width ; 

__attribute__((used)) static bool win32_display_server_set_resolution(void *data,
      unsigned width, unsigned height, int int_hz, float hz, int center, int monitor_index, int xoffset)
{
   DEVMODE curDevmode;
   int iModeNum;
   int freq               = int_hz;
   int depth              = 0;
   dispserv_win32_t *serv = (dispserv_win32_t*)data;

   if (!serv)
      return false;

   win32_get_video_output(&curDevmode, -1, sizeof(curDevmode));

   if (win32_orig_width == 0)
      win32_orig_width          = GetSystemMetrics(SM_CXSCREEN);
   win32_orig_refresh        = curDevmode.dmDisplayFrequency;
   if (win32_orig_height == 0)
      win32_orig_height         = GetSystemMetrics(SM_CYSCREEN);

   /* Used to stop super resolution bug */
   if (width == curDevmode.dmPelsWidth)
      width  = 0;
   if (width == 0)
      width = curDevmode.dmPelsWidth;
   if (height == 0)
      height = curDevmode.dmPelsHeight;
   if (depth == 0)
      depth = curDevmode.dmBitsPerPel;
   if (freq == 0)
      freq = curDevmode.dmDisplayFrequency;

   for (iModeNum = 0;; iModeNum++)
   {
      LONG res;
      DEVMODE devmode;

      if (!win32_get_video_output(&devmode, iModeNum, sizeof(devmode)))
         break;

      if (devmode.dmPelsWidth != width)
         continue;

      if (devmode.dmPelsHeight != height)
         continue;

      if (devmode.dmBitsPerPel != depth)
         continue;

      if (devmode.dmDisplayFrequency != freq)
         continue;

      devmode.dmFields |=
            DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;
      res               =
            win32_change_display_settings(NULL, &devmode, CDS_TEST);

      switch (res)
      {
      case DISP_CHANGE_SUCCESSFUL:
         res = win32_change_display_settings(NULL, &devmode, 0);
         switch (res)
         {
            case DISP_CHANGE_SUCCESSFUL:
               return true;
            case DISP_CHANGE_NOTUPDATED:
               return true;
            default:
               break;
         }
         break;
      case DISP_CHANGE_RESTART:
         break;
      default:
         break;
      }
   }

   return true;
}