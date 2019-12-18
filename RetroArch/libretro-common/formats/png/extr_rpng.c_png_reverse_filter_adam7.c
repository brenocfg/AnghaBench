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
typedef  int /*<<< orphan*/  uint32_t ;
struct rpng_process {scalar_t__ adam7_restore_buf_size; int /*<<< orphan*/  inflate_buf; int /*<<< orphan*/ * data; int /*<<< orphan*/  pass_pos; } ;
struct png_ihdr {int dummy; } ;

/* Variables and functions */
#define  IMAGE_PROCESS_END 131 
#define  IMAGE_PROCESS_ERROR 130 
#define  IMAGE_PROCESS_ERROR_END 129 
#define  IMAGE_PROCESS_NEXT 128 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int png_reverse_filter_adam7_iterate (int /*<<< orphan*/ **,struct png_ihdr const*,struct rpng_process*) ; 

__attribute__((used)) static int png_reverse_filter_adam7(uint32_t **data_,
      const struct png_ihdr *ihdr,
      struct rpng_process *pngp)
{
   int ret = png_reverse_filter_adam7_iterate(data_,
         ihdr, pngp);

   switch (ret)
   {
      case IMAGE_PROCESS_ERROR_END:
      case IMAGE_PROCESS_END:
         break;
      case IMAGE_PROCESS_NEXT:
         pngp->pass_pos++;
         return 0;
      case IMAGE_PROCESS_ERROR:
         if (pngp->data)
         {
            free(pngp->data);
            pngp->data = NULL;
         }
         pngp->inflate_buf -= pngp->adam7_restore_buf_size;
         pngp->adam7_restore_buf_size = 0;
         return -1;
   }

   pngp->inflate_buf            -= pngp->adam7_restore_buf_size;
   pngp->adam7_restore_buf_size  = 0;
   return ret;
}