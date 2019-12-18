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
struct nbio_image_handle {int processing_final_state; int is_blocking_on_processing; int is_blocking; int is_finished; int /*<<< orphan*/  ti; } ;
struct TYPE_2__ {int is_finished; scalar_t__ data; } ;
typedef  TYPE_1__ nbio_handle_t ;

/* Variables and functions */
#define  IMAGE_PROCESS_ERROR 129 
#define  IMAGE_PROCESS_ERROR_END 128 
 int /*<<< orphan*/  image_texture_color_convert (unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  image_texture_set_color_shifts (unsigned int*,unsigned int*,unsigned int*,unsigned int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cb_image_upload_generic(void *data, size_t len)
{
   unsigned r_shift, g_shift, b_shift, a_shift;
   nbio_handle_t             *nbio = (nbio_handle_t*)data;
   struct nbio_image_handle *image = (struct nbio_image_handle*)nbio->data;

   if (!image)
      return -1;

   switch (image->processing_final_state)
   {
      case IMAGE_PROCESS_ERROR:
      case IMAGE_PROCESS_ERROR_END:
         return -1;
      default:
         break;
   }

   image_texture_set_color_shifts(&r_shift, &g_shift, &b_shift,
         &a_shift, &image->ti);

   image_texture_color_convert(r_shift, g_shift, b_shift,
         a_shift, &image->ti);

   image->is_blocking_on_processing         = false;
   image->is_blocking                       = true;
   image->is_finished                       = true;
   nbio->is_finished                        = true;

   return 0;
}