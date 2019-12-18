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
struct exynos_data {scalar_t__ size; scalar_t__ pitch; scalar_t__ bpp; scalar_t__ num_pages; scalar_t__ height; scalar_t__ width; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_restore_crtc () ; 
 int /*<<< orphan*/ * g_drm_mode ; 

__attribute__((used)) static void exynos_deinit(struct exynos_data *pdata)
{
   drm_restore_crtc();

   g_drm_mode       = NULL;
   pdata->width     = 0;
   pdata->height    = 0;
   pdata->num_pages = 0;
   pdata->bpp       = 0;
   pdata->pitch     = 0;
   pdata->size      = 0;
}