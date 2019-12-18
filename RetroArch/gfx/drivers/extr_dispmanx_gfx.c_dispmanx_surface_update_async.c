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
struct dispmanx_surface {int /*<<< orphan*/  bmp_rect; int /*<<< orphan*/  pitch; int /*<<< orphan*/  pixformat; struct dispmanx_page* pages; } ;
struct dispmanx_page {int /*<<< orphan*/  resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  vc_dispmanx_resource_write_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dispmanx_surface_update_async(const void *frame, struct dispmanx_surface *surface)
{
   struct dispmanx_page       *page = NULL;

   /* Since it's an async update, there's no need for multiple pages */
   page = &(surface->pages[0]);

   /* Frame blitting. Nothing else is needed if we only have a page. */
   vc_dispmanx_resource_write_data(page->resource, surface->pixformat,
         surface->pitch, (void*)frame, &(surface->bmp_rect));
}