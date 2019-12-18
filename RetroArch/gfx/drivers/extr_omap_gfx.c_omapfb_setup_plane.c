#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct omapfb_plane_info {int pos_x; int pos_y; int out_width; int out_height; scalar_t__ enabled; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int nat_w; int nat_h; int bpp; int num_pages; TYPE_2__* current_state; int /*<<< orphan*/  fd; } ;
typedef  TYPE_3__ omapfb_data_t ;
struct TYPE_6__ {int size; } ;
struct TYPE_7__ {struct omapfb_plane_info pi; TYPE_1__ mi; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAPFB_QUERY_PLANE ; 
 int /*<<< orphan*/  OMAPFB_SETUP_PLANE ; 
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int,int,int,int) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct omapfb_plane_info*) ; 
 float omapfb_scaling (TYPE_3__*,int,int) ; 

__attribute__((used)) static int omapfb_setup_plane(omapfb_data_t *pdata, int width, int height)
{
   int x, y;
   struct omapfb_plane_info pi = {0};
   float scale = omapfb_scaling(pdata, width, height);
   int w = (int)(scale * width);
   int h = (int)(scale * height);

   RARCH_LOG("omap_video: scaling %dx%d to %dx%d\n", width, height, w, h);

   x = pdata->nat_w / 2 - w / 2;
   y = pdata->nat_h / 2 - h / 2;

   if (width * height * pdata->bpp * pdata->num_pages > pdata->current_state->mi.size)
   {
      RARCH_ERR("omap_video: fb dimensions too large for allocated buffer\n");
      return -1;
   }

   if (ioctl(pdata->fd, OMAPFB_QUERY_PLANE, &pi) != 0)
   {
      RARCH_ERR("[video_omap]: setup plane (query) failed\n");
      return -1;
   }

   /* Disable the plane during setup to avoid garbage on screen. */
   pi.pos_x      = x;
   pi.pos_y      = y;
   pi.out_width  = w;
   pi.out_height = h;
   pi.enabled    = 0;

   if (ioctl(pdata->fd, OMAPFB_SETUP_PLANE, &pi) != 0)
   {
      RARCH_ERR("[video_omap]: setup plane (param = %d %d %d %d) failed\n", x, y, w, h);
      return -1;
   }

   pdata->current_state->pi = pi;

   return 0;
}