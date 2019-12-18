#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structrp ;
typedef  scalar_t__ png_size_t ;
typedef  int /*<<< orphan*/ * png_bytep ;
struct TYPE_6__ {scalar_t__ save_buffer_size; scalar_t__ current_buffer_size; scalar_t__ save_buffer_max; scalar_t__ buffer_size; int /*<<< orphan*/ * save_buffer; int /*<<< orphan*/ * save_buffer_ptr; int /*<<< orphan*/ * current_buffer_ptr; } ;

/* Variables and functions */
 scalar_t__ PNG_SIZE_MAX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ png_malloc_warn (TYPE_1__*,scalar_t__) ; 

void /* PRIVATE */
png_push_save_buffer(png_structrp png_ptr)
{
   if (png_ptr->save_buffer_size != 0)
   {
      if (png_ptr->save_buffer_ptr != png_ptr->save_buffer)
      {
         png_size_t i, istop;
         png_bytep sp;
         png_bytep dp;

         istop = png_ptr->save_buffer_size;
         for (i = 0, sp = png_ptr->save_buffer_ptr, dp = png_ptr->save_buffer;
             i < istop; i++, sp++, dp++)
         {
            *dp = *sp;
         }
      }
   }
   if (png_ptr->save_buffer_size + png_ptr->current_buffer_size >
       png_ptr->save_buffer_max)
   {
      png_size_t new_max;
      png_bytep old_buffer;

      if (png_ptr->save_buffer_size > PNG_SIZE_MAX -
          (png_ptr->current_buffer_size + 256))
      {
         png_error(png_ptr, "Potential overflow of save_buffer");
      }

      new_max = png_ptr->save_buffer_size + png_ptr->current_buffer_size + 256;
      old_buffer = png_ptr->save_buffer;
      png_ptr->save_buffer = (png_bytep)png_malloc_warn(png_ptr,
          (png_size_t)new_max);

      if (png_ptr->save_buffer == NULL)
      {
         png_free(png_ptr, old_buffer);
         png_error(png_ptr, "Insufficient memory for save_buffer");
      }

      if (old_buffer)
         memcpy(png_ptr->save_buffer, old_buffer, png_ptr->save_buffer_size);
      else if (png_ptr->save_buffer_size)
         png_error(png_ptr, "save_buffer error");
      png_free(png_ptr, old_buffer);
      png_ptr->save_buffer_max = new_max;
   }
   if (png_ptr->current_buffer_size)
   {
      memcpy(png_ptr->save_buffer + png_ptr->save_buffer_size,
         png_ptr->current_buffer_ptr, png_ptr->current_buffer_size);
      png_ptr->save_buffer_size += png_ptr->current_buffer_size;
      png_ptr->current_buffer_size = 0;
   }
   png_ptr->save_buffer_ptr = png_ptr->save_buffer;
   png_ptr->buffer_size = 0;
}