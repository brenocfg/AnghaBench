#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct exynos_page {int used; int clear; int /*<<< orphan*/  buf_id; struct exynos_bo* bo; struct exynos_data* base; } ;
struct exynos_device {int dummy; } ;
struct exynos_data {unsigned int num_pages; int bpp; struct exynos_device* device; struct exynos_page* pages; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ pitch; int /*<<< orphan*/  size; struct exynos_bo** buf; } ;
struct exynos_bo {scalar_t__ handle; } ;
struct TYPE_2__ {unsigned int width; unsigned int height; unsigned int bpp; } ;

/* Variables and functions */
 scalar_t__ DRM_FORMAT_RGB565 ; 
 scalar_t__ DRM_FORMAT_XRGB8888 ; 
 unsigned int EXYNOS_BUFFER_COUNT ; 
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 scalar_t__ calloc (unsigned int,int) ; 
 TYPE_1__* defaults ; 
 scalar_t__ drmModeAddFB2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,unsigned int const) ; 
 scalar_t__ drmModeSetCrtc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct exynos_bo* exynos_bo_create (struct exynos_device*,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  exynos_bo_destroy (struct exynos_bo*) ; 
 int /*<<< orphan*/  exynos_clean_up_pages (struct exynos_page*,int) ; 
 struct exynos_bo* exynos_create_mapped_buffer (struct exynos_device*,unsigned int const) ; 
 struct exynos_device* exynos_device_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_device_destroy (struct exynos_device*) ; 
 int /*<<< orphan*/  g_crtc_id ; 
 int /*<<< orphan*/  g_drm_connector_id ; 
 int /*<<< orphan*/  g_drm_fd ; 
 int /*<<< orphan*/  g_drm_mode ; 

__attribute__((used)) static int exynos_alloc(struct exynos_data *pdata)
{
   struct exynos_bo *bo;
   struct exynos_page *pages;
   unsigned i;
   uint32_t pixel_format;
   const unsigned flags = 0;
   uint32_t handles[4] = {0}, pitches[4] = {0}, offsets[4] = {0};
   struct exynos_device *device = exynos_device_create(g_drm_fd);

   if (!device)
   {
      RARCH_ERR("[video_exynos]: failed to create device from fd\n");
      return -1;
   }

   pages = (struct exynos_page*)calloc(pdata->num_pages,
         sizeof(struct exynos_page));

   if (!pages)
   {
      RARCH_ERR("[video_exynos]: failed to allocate pages\n");
      goto fail_alloc;
   }

   for (i = 0; i < EXYNOS_BUFFER_COUNT; ++i)
   {
      const unsigned buffer_size = defaults[i].width * defaults[i].height * defaults[i].bpp;

      bo = exynos_create_mapped_buffer(device, buffer_size);
      if (!bo)
         break;

      pdata->buf[i] = bo;
   }

   if (i != EXYNOS_BUFFER_COUNT)
   {
      while (i-- > 0)
      {
         exynos_bo_destroy(pdata->buf[i]);
         pdata->buf[i] = NULL;
      }

      goto fail;
   }

   for (i = 0; i < pdata->num_pages; ++i)
   {
      bo = exynos_bo_create(device, pdata->size, flags);
      if (!bo)
      {
         RARCH_ERR("[video_exynos]: failed to create buffer object\n");
         goto fail;
      }

      /* Don't map the BO, since we don't access it through userspace. */

      pages[i].bo    = bo;
      pages[i].base  = pdata;

      pages[i].used  = false;
      pages[i].clear = true;
   }

   pixel_format = (pdata->bpp == 2) ? DRM_FORMAT_RGB565 : DRM_FORMAT_XRGB8888;
   pitches[0]   = pdata->pitch;
   offsets[0]   = 0;

   for (i = 0; i < pdata->num_pages; ++i)
   {
      handles[0] = pages[i].bo->handle;

      if (drmModeAddFB2(g_drm_fd, pdata->width, pdata->height,
               pixel_format, handles, pitches, offsets,
               &pages[i].buf_id, flags))
      {
         RARCH_ERR("[video_exynos]: failed to add bo %u to fb\n", i);
         goto fail;
      }
   }

   /* Setup CRTC: display the last allocated page. */
   if (drmModeSetCrtc(g_drm_fd, g_crtc_id,
            pages[pdata->num_pages - 1].buf_id,
            0, 0, &g_drm_connector_id, 1, g_drm_mode))
   {
      RARCH_ERR("[video_exynos]: initial CRTC setup failed.\n");
      goto fail;
   }

   pdata->pages  = pages;
   pdata->device = device;

   return 0;

fail:
   exynos_clean_up_pages(pages, pdata->num_pages);

fail_alloc:
   exynos_device_destroy(device);

   return -1;
}