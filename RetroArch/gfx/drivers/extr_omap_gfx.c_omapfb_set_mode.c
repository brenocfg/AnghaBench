#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  fd; scalar_t__ sync; } ;
typedef  TYPE_1__ omapfb_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  OMAPFB_WAITFORGO ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ omapfb_enable_plane (TYPE_1__*) ; 
 scalar_t__ omapfb_setup_pages (TYPE_1__*) ; 
 scalar_t__ omapfb_setup_plane (TYPE_1__*,int,int) ; 
 scalar_t__ omapfb_setup_screeninfo (TYPE_1__*,int,int) ; 

__attribute__((used)) static int omapfb_set_mode(omapfb_data_t *pdata, int width, int height)
{
   if (pdata->sync)
      ioctl(pdata->fd, OMAPFB_WAITFORGO);

   if (omapfb_setup_plane(pdata, width, height) != 0)
      return -1;

   if (omapfb_setup_screeninfo(pdata, width, height) != 0 ||
         omapfb_setup_pages(pdata) != 0 ||
         omapfb_enable_plane(pdata) != 0)
      return -1;

   return 0;
}