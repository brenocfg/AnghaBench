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
struct dispmanx_video {scalar_t__ pageflip_pending; int /*<<< orphan*/  update; int /*<<< orphan*/  pending_mutex; int /*<<< orphan*/  vsync_condition; } ;
struct dispmanx_surface {int numpages; int used; int /*<<< orphan*/  element; struct dispmanx_surface* pages; int /*<<< orphan*/  page_used_mutex; int /*<<< orphan*/  resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct dispmanx_surface*) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_element_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_resource_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_update_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_update_submit_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispmanx_surface_free(struct dispmanx_video *_dispvars,
      struct dispmanx_surface **sp)
{
   int i;
   struct dispmanx_surface *surface = *sp;

   /* What if we run into the vsync cb code after freeing the surface?
    * We could be trying to get non-existant lock, signal non-existant condition..
    * So we wait for any pending flips to complete before freeing any surface. */
   slock_lock(_dispvars->pending_mutex);
   if (_dispvars->pageflip_pending > 0)
      scond_wait(_dispvars->vsync_condition, _dispvars->pending_mutex);
   slock_unlock(_dispvars->pending_mutex);

   for (i = 0; i < surface->numpages; i++)
   {
      vc_dispmanx_resource_delete(surface->pages[i].resource);
      surface->pages[i].used = false;
      slock_free(surface->pages[i].page_used_mutex);
   }

   free(surface->pages);

   _dispvars->update = vc_dispmanx_update_start(0);
   vc_dispmanx_element_remove(_dispvars->update, surface->element);
   vc_dispmanx_update_submit_sync(_dispvars->update);

   free(surface);
   *sp = NULL;
}