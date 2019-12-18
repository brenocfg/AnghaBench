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
struct TYPE_2__ {unsigned int width; unsigned int height; int /*<<< orphan*/  pixels; } ;
struct nbio_image_handle {TYPE_1__ ti; int /*<<< orphan*/  size; int /*<<< orphan*/  type; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int IMAGE_PROCESS_ERROR ; 
 int /*<<< orphan*/  image_transfer_is_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int image_transfer_process (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int task_image_process(
      struct nbio_image_handle *image,
      unsigned *width,
      unsigned *height)
{
   int retval;

   if (!image_transfer_is_valid(image->handle, image->type))
      return IMAGE_PROCESS_ERROR;

   retval = image_transfer_process(
         image->handle,
         image->type,
         &image->ti.pixels, image->size, width, height);

   if (retval == IMAGE_PROCESS_ERROR)
      return IMAGE_PROCESS_ERROR;

   image->ti.width  = *width;
   image->ti.height = *height;

   return retval;
}