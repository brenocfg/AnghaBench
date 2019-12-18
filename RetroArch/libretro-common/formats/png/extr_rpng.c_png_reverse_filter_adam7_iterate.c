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
struct png_ihdr {int dummy; } ;
struct rpng_process {size_t pass_pos; int adam7_pass_initialized; scalar_t__ pass_size; int /*<<< orphan*/  pass_height; int /*<<< orphan*/  pass_width; int /*<<< orphan*/ * data; int /*<<< orphan*/  total_out; int /*<<< orphan*/  adam7_restore_buf_size; int /*<<< orphan*/  inflate_buf; struct png_ihdr const ihdr; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int IMAGE_PROCESS_END ; 
 int IMAGE_PROCESS_ERROR ; 
 int IMAGE_PROCESS_ERROR_END ; 
 int IMAGE_PROCESS_NEXT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * passes ; 
 int /*<<< orphan*/  png_reverse_filter_adam7_deinterlace_pass (int /*<<< orphan*/ *,struct png_ihdr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int png_reverse_filter_init (struct png_ihdr const*,struct rpng_process*) ; 
 int png_reverse_filter_regular_iterate (int /*<<< orphan*/ **,struct png_ihdr const*,struct rpng_process*) ; 

__attribute__((used)) static int png_reverse_filter_adam7_iterate(uint32_t **data_,
      const struct png_ihdr *ihdr,
      struct rpng_process *pngp)
{
   int        ret = 0;
   bool   to_next = pngp->pass_pos < ARRAY_SIZE(passes);
   uint32_t *data = *data_;

   if (!to_next)
      return IMAGE_PROCESS_END;

   ret = png_reverse_filter_init(ihdr, pngp);

   if (ret == 1)
      return IMAGE_PROCESS_NEXT;
   if (ret == -1)
      return IMAGE_PROCESS_ERROR_END;

   if (png_reverse_filter_init(&pngp->ihdr, pngp) == -1)
      return IMAGE_PROCESS_ERROR;

   do{
      ret = png_reverse_filter_regular_iterate(&pngp->data,
            &pngp->ihdr, pngp);
   }while(ret == IMAGE_PROCESS_NEXT);

   if (ret == IMAGE_PROCESS_ERROR || ret == IMAGE_PROCESS_ERROR_END)
      return IMAGE_PROCESS_ERROR;

   pngp->inflate_buf            += pngp->pass_size;
   pngp->adam7_restore_buf_size += pngp->pass_size;

   pngp->total_out              -= pngp->pass_size;

   png_reverse_filter_adam7_deinterlace_pass(data,
         ihdr, pngp->data, pngp->pass_width, pngp->pass_height, &passes[pngp->pass_pos]);

   free(pngp->data);

   pngp->data = NULL;
   pngp->pass_width  = 0;
   pngp->pass_height = 0;
   pngp->pass_size   = 0;
   pngp->adam7_pass_initialized = false;

   return IMAGE_PROCESS_NEXT;
}