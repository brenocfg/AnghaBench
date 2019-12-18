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
struct omapfb_plane_info {int enabled; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ omapfb_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  OMAPFB_QUERY_PLANE ; 
 int /*<<< orphan*/  OMAPFB_SETUP_PLANE ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct omapfb_plane_info*) ; 

__attribute__((used)) static int omapfb_enable_plane(omapfb_data_t *pdata)
{
   struct omapfb_plane_info pi = {0};

   if (ioctl(pdata->fd, OMAPFB_QUERY_PLANE, &pi) != 0)
   {
      RARCH_ERR("[video_omap]: enable plane (query) failed\n");
      return -1;
   }

   pi.enabled = 1;

   if (ioctl(pdata->fd, OMAPFB_SETUP_PLANE, &pi) != 0)
   {
      RARCH_ERR("[video_omap]: enable plane failed\n");
      return -1;
   }

   return 0;
}