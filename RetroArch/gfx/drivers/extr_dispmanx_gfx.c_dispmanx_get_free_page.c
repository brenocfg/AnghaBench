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
struct dispmanx_video {scalar_t__ pageflip_pending; int /*<<< orphan*/  pending_mutex; int /*<<< orphan*/  vsync_condition; } ;
struct dispmanx_surface {unsigned int numpages; struct dispmanx_page* pages; } ;
struct dispmanx_page {int used; int /*<<< orphan*/  page_used_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dispmanx_page *dispmanx_get_free_page(struct dispmanx_video *_dispvars,
      struct dispmanx_surface *surface)
{
   unsigned i;
   struct dispmanx_page *page = NULL;

   while (!page)
   {
      /* Try to find a free page */
      for (i = 0; i < surface->numpages; ++i)
      {
         if (!surface->pages[i].used)
         {
            page = (surface->pages) + i;
            break;
         }
      }

      /* If no page is free at the moment,
       * wait until a free page is freed by vsync CB. */
      if (!page)
      {
         slock_lock(_dispvars->pending_mutex);
          if (_dispvars->pageflip_pending > 0)
             scond_wait(_dispvars->vsync_condition, _dispvars->pending_mutex);
         slock_unlock(_dispvars->pending_mutex);
      }
   }

   /* We mark the choosen page as used */
   slock_lock(page->page_used_mutex);
   page->used = true;
   slock_unlock(page->page_used_mutex);

   return page;
}