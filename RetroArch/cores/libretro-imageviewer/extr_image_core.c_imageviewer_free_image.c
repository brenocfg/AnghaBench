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

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * image_buffer ; 
 int /*<<< orphan*/  image_texture ; 
 int /*<<< orphan*/  image_texture_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void imageviewer_free_image(void)
{
#ifdef STB_IMAGE_IMPLEMENTATION
   if (image_buffer)
      free(image_buffer);
#else
   image_texture_free(&image_texture);
#endif
   image_buffer = NULL;
}