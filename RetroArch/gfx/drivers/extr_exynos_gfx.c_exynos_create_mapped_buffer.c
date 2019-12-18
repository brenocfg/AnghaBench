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
struct exynos_device {int dummy; } ;
struct exynos_bo {int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 struct exynos_bo* exynos_bo_create (struct exynos_device*,unsigned int,unsigned int const) ; 
 int /*<<< orphan*/  exynos_bo_destroy (struct exynos_bo*) ; 
 int /*<<< orphan*/  exynos_bo_map (struct exynos_bo*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static struct exynos_bo *exynos_create_mapped_buffer(
      struct exynos_device *dev, unsigned size)
{
   const unsigned flags = 0;
   struct exynos_bo *buf = exynos_bo_create(dev, size, flags);

   if (!buf)
   {
      RARCH_ERR("[video_exynos]: failed to create temp buffer object\n");
      return NULL;
   }

   if (!exynos_bo_map(buf))
   {
      RARCH_ERR("[video_exynos]: failed to map temp buffer object\n");
      exynos_bo_destroy(buf);
      return NULL;
   }

   memset(buf->vaddr, 0, size);

   return buf;
}