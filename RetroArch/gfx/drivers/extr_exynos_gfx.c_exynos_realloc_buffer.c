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
struct exynos_data {TYPE_1__** src; struct exynos_bo** buf; int /*<<< orphan*/  device; } ;
struct exynos_bo {unsigned int size; int /*<<< orphan*/  handle; } ;
typedef  enum exynos_buffer_type { ____Placeholder_exynos_buffer_type } exynos_buffer_type ;
struct TYPE_4__ {int buf_type; } ;
struct TYPE_3__ {int /*<<< orphan*/ * bo; } ;

/* Variables and functions */
 unsigned int EXYNOS_IMAGE_COUNT ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 TYPE_2__* defaults ; 
 int /*<<< orphan*/  exynos_bo_destroy (struct exynos_bo*) ; 
 int /*<<< orphan*/  exynos_buffer_name (int) ; 
 struct exynos_bo* exynos_create_mapped_buffer (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int exynos_realloc_buffer(struct exynos_data *pdata,
      enum exynos_buffer_type type, unsigned size)
{
   struct exynos_bo *buf = pdata->buf[type];

   if (!buf)
      return -1;

   if (size > buf->size)
   {
      unsigned i;

#if (EXYNOS_GFX_DEBUG_LOG == 1)
      RARCH_LOG("[video_exynos]: reallocating %s buffer (%u -> %u bytes)\n",
            exynos_buffer_name(type), buf->size, size);
#endif

      exynos_bo_destroy(buf);
      buf = exynos_create_mapped_buffer(pdata->device, size);

      if (!buf)
      {
         RARCH_ERR("[video_exynos]: reallocation failed\n");
         return -1;
      }

      pdata->buf[type] = buf;

      /* Map new GEM buffer to the G2D images backed by it. */
      for (i = 0; i < EXYNOS_IMAGE_COUNT; ++i)
      {
         if (defaults[i].buf_type == type)
            pdata->src[i]->bo[0] = buf->handle;
      }
   }

   return 0;
}