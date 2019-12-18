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
struct exynos_data {int /*<<< orphan*/  drmname; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int /*<<< orphan*/  connector_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  page_flip_handler; int /*<<< orphan*/  version; } ;
struct TYPE_4__ {int fd; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_EVENT_CONTEXT_VERSION ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  drm_free () ; 
 int /*<<< orphan*/  drm_get_decoder (int) ; 
 int /*<<< orphan*/  drm_get_encoder (int) ; 
 int /*<<< orphan*/  drm_get_resources (int) ; 
 int exynos_get_device_index () ; 
 int /*<<< orphan*/  exynos_page_flip_handler ; 
 TYPE_3__* g_drm_connector ; 
 TYPE_2__ g_drm_evctx ; 
 int g_drm_fd ; 
 TYPE_1__ g_drm_fds ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int exynos_open(struct exynos_data *pdata)
{
   unsigned i;
   int fd                                 = -1;
   char buf[32]                           = {0};
   int devidx                             = exynos_get_device_index();

   if (pdata)
      g_drm_fd                            = -1;

   if (devidx != -1)
      snprintf(buf, sizeof(buf), "/dev/dri/card%d", devidx);
   else
   {
      RARCH_ERR("[video_exynos]: no compatible DRM device found\n");
      return -1;
   }

   fd = open(buf, O_RDWR);

   if (fd < 0)
   {
      RARCH_ERR("[video_exynos]: can't open DRM device\n");
      return -1;
   }

   if (!drm_get_resources(fd))
      goto fail;

   if (!drm_get_decoder(fd))
      goto fail;

   if (!drm_get_encoder(fd))
      goto fail;

   /* Setup the flip handler. */
   g_drm_fds.fd                         = fd;
   g_drm_fds.events                     = POLLIN;
   g_drm_evctx.version                  = DRM_EVENT_CONTEXT_VERSION;
   g_drm_evctx.page_flip_handler        = exynos_page_flip_handler;

   strncpy(pdata->drmname, buf, sizeof(buf));
   g_drm_fd = fd;

   RARCH_LOG("[video_exynos]: using DRM device \"%s\" with connector id %u.\n",
         pdata->drmname, g_drm_connector->connector_id);

   return 0;

fail:
   drm_free();
   close(g_drm_fd);

   return -1;
}