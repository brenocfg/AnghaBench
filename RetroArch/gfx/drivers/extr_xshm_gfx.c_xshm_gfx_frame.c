#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ shmaddr; } ;
struct TYPE_4__ {int width; int /*<<< orphan*/  display; int /*<<< orphan*/  height; int /*<<< orphan*/  image; int /*<<< orphan*/  gc; int /*<<< orphan*/  wndw; TYPE_1__ shmInfo; } ;
typedef  TYPE_2__ xshm_t ;
typedef  int /*<<< orphan*/  video_frame_info_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XShmPutImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  menu_driver_frame (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool xshm_gfx_frame(void *data, const void *frame, unsigned width,
      unsigned height, uint64_t frame_count,
      unsigned pitch, const char *msg, video_frame_info_t *video_info)
{
   xshm_t* xshm = (xshm_t*)data;
   int y;

   for (y=0;y<height;y++)
   {
      memcpy((uint8_t*)xshm->shmInfo.shmaddr + sizeof(uint32_t)*xshm->width*y,
            (uint8_t*)frame + pitch*y, pitch);
   }

#ifdef HAVE_MENU
   menu_driver_frame(video_info);
#endif

   XShmPutImage(xshm->display, xshm->wndw, xshm->gc, xshm->image,
                0, 0, 0, 0, xshm->width, xshm->height, False);
   XFlush(xshm->display);

   return true;
}