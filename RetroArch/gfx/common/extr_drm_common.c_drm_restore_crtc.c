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
struct TYPE_3__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  buffer_id; int /*<<< orphan*/  crtc_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  drmModeFreeCrtc (TYPE_1__*) ; 
 int /*<<< orphan*/  drmModeSetCrtc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_connector_id ; 
 int /*<<< orphan*/  g_drm_fd ; 
 TYPE_1__* g_orig_crtc ; 

void drm_restore_crtc(void)
{
   if (!g_orig_crtc)
      return;

   drmModeSetCrtc(g_drm_fd, g_orig_crtc->crtc_id,
         g_orig_crtc->buffer_id,
         g_orig_crtc->x,
         g_orig_crtc->y,
         &g_connector_id, 1, &g_orig_crtc->mode);

   drmModeFreeCrtc(g_orig_crtc);
   g_orig_crtc = NULL;
}