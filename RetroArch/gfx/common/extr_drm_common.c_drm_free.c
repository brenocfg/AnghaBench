#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pollfd {int dummy; } ;
typedef  int /*<<< orphan*/  drmEventContext ;

/* Variables and functions */
 int /*<<< orphan*/  drmModeFreeConnector (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drmModeFreeEncoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drmModeFreeResources (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_drm_connector ; 
 int /*<<< orphan*/ * g_drm_encoder ; 
 int /*<<< orphan*/  g_drm_evctx ; 
 int /*<<< orphan*/  g_drm_fds ; 
 int /*<<< orphan*/ * g_drm_resources ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void drm_free(void)
{
   if (g_drm_encoder)
      drmModeFreeEncoder(g_drm_encoder);
   if (g_drm_connector)
      drmModeFreeConnector(g_drm_connector);
   if (g_drm_resources)
      drmModeFreeResources(g_drm_resources);

   memset(&g_drm_fds,     0, sizeof(struct pollfd));
   memset(&g_drm_evctx,   0, sizeof(drmEventContext));

   g_drm_encoder      = NULL;
   g_drm_connector    = NULL;
   g_drm_resources    = NULL;
}