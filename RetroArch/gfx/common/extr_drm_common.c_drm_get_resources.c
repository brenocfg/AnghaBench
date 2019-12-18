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

/* Variables and functions */
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 int /*<<< orphan*/  drmModeGetResources (int) ; 
 int /*<<< orphan*/  g_drm_resources ; 

bool drm_get_resources(int fd)
{
   g_drm_resources = drmModeGetResources(fd);
   if (!g_drm_resources)
   {
      RARCH_WARN("[DRM]: Couldn't get device resources.\n");
      return false;
   }

   return true;
}