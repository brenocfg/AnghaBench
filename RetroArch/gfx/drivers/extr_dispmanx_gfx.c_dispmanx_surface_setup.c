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
struct dispmanx_video {float dispmanx_height; int dispmanx_width; int /*<<< orphan*/  update; int /*<<< orphan*/  display; int /*<<< orphan*/  vc_image_ptr; } ;
struct TYPE_4__ {int opacity; scalar_t__ mask; int /*<<< orphan*/  flags; } ;
struct dispmanx_surface {int numpages; TYPE_2__ alpha; int /*<<< orphan*/  src_rect; TYPE_1__* pages; int /*<<< orphan*/  dst_rect; int /*<<< orphan*/  element; int /*<<< orphan*/  bmp_rect; TYPE_1__* next_page; int /*<<< orphan*/  pitch; } ;
struct dispmanx_page {int dummy; } ;
typedef  scalar_t__ VC_IMAGE_TYPE_T ;
struct TYPE_3__ {int used; int /*<<< orphan*/  resource; int /*<<< orphan*/  page_used_mutex; struct dispmanx_video* dispvars; struct dispmanx_surface* surface; } ;
typedef  int /*<<< orphan*/  DISPMANX_TRANSFORM_T ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN_UP (int,int) ; 
 int /*<<< orphan*/  DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS ; 
 int /*<<< orphan*/  DISPMANX_PROTECTION_NONE ; 
 scalar_t__ VC_IMAGE_XRGB8888 ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  slock_new () ; 
 int /*<<< orphan*/  vc_dispmanx_element_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_rect_set (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  vc_dispmanx_resource_create (scalar_t__,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_dispmanx_update_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_update_submit_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispmanx_surface_setup(struct dispmanx_video *_dispvars,
      int src_width, int src_height,
      int visible_pitch, int bpp, VC_IMAGE_TYPE_T pixformat,
      int alpha, float aspect, int numpages, int layer,
      struct dispmanx_surface **sp)
{
   int i, dst_width, dst_height, dst_xpos, dst_ypos, visible_width;
   struct dispmanx_surface *surface = NULL;

   *sp = calloc(1, sizeof(struct dispmanx_surface));

   surface = *sp;

   /* Setup surface parameters */
   surface->numpages = numpages;
   /* We receive the pitch for what we consider "useful info",
    * excluding things that are between scanlines.
    * Then we align it to 16 pixels (not bytes) for performance reasons. */
   surface->pitch = ALIGN_UP(visible_pitch, (pixformat == VC_IMAGE_XRGB8888 ? 64 : 32));

   /* Transparency disabled */
   surface->alpha.flags = DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS;
   surface->alpha.opacity = alpha;
   surface->alpha.mask = 0;

   /* Allocate memory for all the pages in each surface
    * and initialize variables inside each page's struct. */
   surface->pages = calloc(surface->numpages, sizeof(struct dispmanx_page));

   for (i = 0; i < surface->numpages; i++)
   {
      surface->pages[i].used = false;
      surface->pages[i].surface = surface;
      surface->pages[i].dispvars = _dispvars;
      surface->pages[i].page_used_mutex = slock_new();
   }

   /* No need to mutex this access to the "used" member because
    * the flipping/callbacks are not still running */
   surface->next_page = &(surface->pages[0]);
   surface->next_page->used = true;

   /* The "visible" width obtained from the core pitch. We blit based on
    * the "visible" width, for cores with things between scanlines. */
   visible_width = visible_pitch / (bpp / 8);

   dst_width  = _dispvars->dispmanx_height * aspect;
   dst_height = _dispvars->dispmanx_height;

   /* If we obtain a scaled image width that is bigger than the physical screen width,
    * then we keep the physical screen width as our maximun width. */
   if (dst_width > _dispvars->dispmanx_width)
      dst_width = _dispvars->dispmanx_width;

   dst_xpos = (_dispvars->dispmanx_width - dst_width) / 2;
   dst_ypos = (_dispvars->dispmanx_height - dst_height) / 2;

   /* We configure the rects now. */
   vc_dispmanx_rect_set(&surface->dst_rect, dst_xpos, dst_ypos, dst_width, dst_height);
   vc_dispmanx_rect_set(&surface->bmp_rect, 0, 0, src_width, src_height);
   vc_dispmanx_rect_set(&surface->src_rect, 0, 0, src_width << 16, src_height << 16);

   for (i = 0; i < surface->numpages; i++)
   {
      surface->pages[i].resource = vc_dispmanx_resource_create(pixformat,
            visible_width, src_height, &(_dispvars->vc_image_ptr));
   }
   /* Add element. */
   _dispvars->update = vc_dispmanx_update_start(0);

   surface->element = vc_dispmanx_element_add(
         _dispvars->update,_dispvars->display, layer,
         &surface->dst_rect, surface->pages[0].resource,
         &surface->src_rect, DISPMANX_PROTECTION_NONE,
         &surface->alpha, 0, (DISPMANX_TRANSFORM_T)0);

   vc_dispmanx_update_submit_sync(_dispvars->update);
}