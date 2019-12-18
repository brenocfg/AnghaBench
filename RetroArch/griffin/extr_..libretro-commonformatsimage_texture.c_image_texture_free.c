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
struct texture_image {int /*<<< orphan*/ * pixels; scalar_t__ height; scalar_t__ width; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void image_texture_free(struct texture_image *img)
{
   if (!img)
      return;

   if (img->pixels)
      free(img->pixels);
   img->width  = 0;
   img->height = 0;
   img->pixels = NULL;
}