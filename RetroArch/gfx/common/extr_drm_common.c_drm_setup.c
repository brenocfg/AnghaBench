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
struct TYPE_4__ {int /*<<< orphan*/  connector_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  crtc_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 int /*<<< orphan*/  drmModeGetCrtc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_connector_id ; 
 int /*<<< orphan*/  g_crtc_id ; 
 TYPE_2__* g_drm_connector ; 
 TYPE_1__* g_drm_encoder ; 
 int /*<<< orphan*/  g_orig_crtc ; 

void drm_setup(int fd)
{
   g_crtc_id        = g_drm_encoder->crtc_id;
   g_connector_id   = g_drm_connector->connector_id;
   g_orig_crtc      = drmModeGetCrtc(fd, g_crtc_id);
   if (!g_orig_crtc)
      RARCH_WARN("[DRM]: Cannot find original CRTC.\n");
}