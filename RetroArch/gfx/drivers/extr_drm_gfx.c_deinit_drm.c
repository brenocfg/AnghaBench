#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fb_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  fd; TYPE_1__* orig_crtc; int /*<<< orphan*/  connector_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  buffer_id; int /*<<< orphan*/  crtc_id; } ;

/* Variables and functions */
 TYPE_3__* bufs ; 
 TYPE_2__ drm ; 
 int /*<<< orphan*/  drmModeRmFB (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  drmModeSetCrtc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void deinit_drm(void)
{
   /* Restore the original videomode/connector/scanoutbuffer(fb)
    * combination (the original CRTC, that is). */
   drmModeSetCrtc(drm.fd, drm.orig_crtc->crtc_id,
         drm.orig_crtc->buffer_id,
         drm.orig_crtc->x, drm.orig_crtc->y,
         &drm.connector_id, 1, &drm.orig_crtc->mode);

#if 0
   /* TODO: Free surfaces here along
    * with their pages (framebuffers)! */

   if (bufs[0].fb_id)
   {
      drmModeRmFB(drm.fd, bufs[0].fb_id);
      drmModeRmFB(drm.fd, bufs[1].fb_id);
   }
#endif
}