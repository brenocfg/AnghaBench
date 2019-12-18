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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_video {int dummy; } ;
struct drm_surface {int numpages; int total_pitch; int pitch; int bpp; int src_width; int src_height; float aspect; scalar_t__ flip_page; struct drm_page* pages; int /*<<< orphan*/  pixformat; } ;
struct TYPE_3__ {int width; int height; } ;
struct drm_page {int used; TYPE_1__ buf; int /*<<< orphan*/  page_used_mutex; struct drm_video* drmvars; struct drm_surface* surface; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 struct drm_surface* calloc (int,int) ; 
 TYPE_2__ drm ; 
 int modeset_create_dumbfb (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_new () ; 

__attribute__((used)) static void drm_surface_setup(void *data,  int src_width, int src_height,
      int pitch, int bpp, uint32_t pixformat,
      int alpha, float aspect, int numpages, int layer,
      struct drm_surface **sp)
{
   struct drm_video *_drmvars = data;
   int i;
   struct drm_surface *surface = NULL;

   *sp = calloc (1, sizeof(struct drm_surface));

   surface = *sp;

   /* Setup surface parameters */
   surface->numpages = numpages;
   /* We receive the total pitch, including things that are
    * between scanlines and we calculate the visible pitch
    * from the visible width.
    *
    * These will be used to increase the offsets for blitting. */
   surface->total_pitch = pitch;
   surface->pitch       = src_width * bpp;
   surface->bpp         = bpp;
   surface->pixformat   = pixformat;
   surface->src_width   = src_width;
   surface->src_height  = src_height;
   surface->aspect      = aspect;

   /* Allocate memory for all the pages in each surface
    * and initialize variables inside each page's struct. */
   surface->pages = (struct drm_page*)
      calloc(surface->numpages, sizeof(struct drm_page));

   for (i = 0; i < surface->numpages; i++)
   {
      surface->pages[i].used            = false;
      surface->pages[i].surface         = surface;
      surface->pages[i].drmvars         = _drmvars;
      surface->pages[i].page_used_mutex = slock_new();
   }

   /* Create the framebuffer for each one of the pages of the surface. */
   for (i = 0; i < surface->numpages; i++)
   {
      surface->pages[i].buf.width  = src_width;
      surface->pages[i].buf.height = src_height;
      int ret                      = modeset_create_dumbfb(
            drm.fd, &surface->pages[i].buf, bpp, pixformat);

      if (ret)
      {
         RARCH_ERR ("DRM: can't create fb\n");
      }
   }

   surface->flip_page = 0;
}