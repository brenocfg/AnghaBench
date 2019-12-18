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
struct g2d_image {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct g2d_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int g2d_exec (struct g2d_context*) ; 
 int g2d_solid_fill (struct g2d_context*,struct g2d_image*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_clear_buffer(struct g2d_context *g2d, struct g2d_image *img)
{
   int ret = g2d_solid_fill(g2d, img, 0, 0, img->width, img->height);

   if (ret == 0)
      ret = g2d_exec(g2d);

   if (ret != 0)
      RARCH_ERR("[video_exynos]: failed to clear buffer using G2D\n");

   return ret;
}