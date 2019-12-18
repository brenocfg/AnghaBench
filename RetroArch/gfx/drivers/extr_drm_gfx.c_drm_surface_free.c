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
struct drm_video {int dummy; } ;
struct drm_surface {int numpages; int used; struct drm_surface* pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct drm_surface*) ; 

__attribute__((used)) static void drm_surface_free(void *data, struct drm_surface **sp)
{
   int i;
   struct drm_video *_drmvars = data;
   struct drm_surface *surface = *sp;

   for (i = 0; i < surface->numpages; i++)
      surface->pages[i].used = false;

   free(surface->pages);

   free(surface);
   *sp = NULL;
}