#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct rpng_process {scalar_t__ stream; TYPE_2__* stream_backend; struct rpng_process* inflate_buf; int /*<<< orphan*/  inflate_initialized; } ;
struct TYPE_8__ {unsigned int width; unsigned int height; } ;
struct TYPE_10__ {struct rpng_process* process; TYPE_1__ ihdr; } ;
typedef  TYPE_3__ rpng_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* stream_free ) (scalar_t__) ;} ;

/* Variables and functions */
 int IMAGE_PROCESS_ERROR ; 
 int IMAGE_PROCESS_NEXT ; 
 int /*<<< orphan*/  free (struct rpng_process*) ; 
 int png_reverse_filter_iterate (TYPE_3__*,int /*<<< orphan*/ **) ; 
 int rpng_load_image_argb_process_inflate_init (TYPE_3__*,int /*<<< orphan*/ **) ; 
 struct rpng_process* rpng_process_init (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

int rpng_process_image(rpng_t *rpng,
      void **_data, size_t size, unsigned *width, unsigned *height)
{
   uint32_t **data = (uint32_t**)_data;

   (void)size;

   if (!rpng->process)
   {
      struct rpng_process *process = rpng_process_init(rpng);

      if (!process)
         goto error;

      rpng->process = process;
      return IMAGE_PROCESS_NEXT;
   }

   if (!rpng->process->inflate_initialized)
   {
      if (rpng_load_image_argb_process_inflate_init(rpng, data) == -1)
         goto error;
      return IMAGE_PROCESS_NEXT;
   }

   *width  = rpng->ihdr.width;
   *height = rpng->ihdr.height;

   return png_reverse_filter_iterate(rpng, data);

error:
   if (rpng->process)
   {
      if (rpng->process->inflate_buf)
         free(rpng->process->inflate_buf);
      if (rpng->process->stream)
         rpng->process->stream_backend->stream_free(rpng->process->stream);
      free(rpng->process);
   }
   return IMAGE_PROCESS_ERROR;
}