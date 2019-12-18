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
struct nbio_image_handle {int is_blocking_on_processing; int is_finished; int /*<<< orphan*/ * cb; } ;
struct TYPE_2__ {scalar_t__ data; } ;
typedef  TYPE_1__ nbio_handle_t ;

/* Variables and functions */
 int IMAGE_PROCESS_END ; 
 int IMAGE_PROCESS_ERROR ; 
 int IMAGE_PROCESS_ERROR_END ; 
 int /*<<< orphan*/  cb_image_upload_generic ; 
 int task_image_process (struct nbio_image_handle*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int cb_image_thumbnail(void *data, size_t len)
{
   unsigned width                   = 0;
   unsigned height                  = 0;
   nbio_handle_t        *nbio       = (nbio_handle_t*)data;
   struct nbio_image_handle *image  = (struct nbio_image_handle*)nbio->data;
   int retval                       = image ? task_image_process(image, &width, &height) : IMAGE_PROCESS_ERROR;

   if ((retval == IMAGE_PROCESS_ERROR)    ||
       (retval == IMAGE_PROCESS_ERROR_END)
      )
      return -1;

   image->is_blocking_on_processing = (retval != IMAGE_PROCESS_END);
   image->is_finished               = (retval == IMAGE_PROCESS_END);
   image->cb                        = &cb_image_upload_generic;

   return 0;
}