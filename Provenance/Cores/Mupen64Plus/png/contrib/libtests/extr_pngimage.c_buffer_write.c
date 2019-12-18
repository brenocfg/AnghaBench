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
struct display {int dummy; } ;
struct buffer_list {scalar_t__ buffer; struct buffer_list* next; } ;
struct buffer {size_t end_count; struct buffer_list* last; } ;
typedef  scalar_t__ png_size_t ;
typedef  size_t png_bytep ;

/* Variables and functions */
 int /*<<< orphan*/  APP_ERROR ; 
 struct buffer_list* buffer_extend (struct buffer_list*) ; 
 int /*<<< orphan*/  display_log (struct display*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,size_t,size_t) ; 

__attribute__((used)) static void
buffer_write(struct display *dp, struct buffer *buffer, png_bytep data,
   png_size_t size)
   /* Generic write function used both from the write callback provided to
    * libpng and from the generic read code.
    */
{
   /* Write the data into the buffer, adding buffers as required */
   struct buffer_list *last = buffer->last;
   size_t end_count = buffer->end_count;

   while (size > 0)
   {
      size_t avail;

      if (end_count >= sizeof last->buffer)
      {
         if (last->next == NULL)
         {
            last = buffer_extend(last);

            if (last == NULL)
               display_log(dp, APP_ERROR, "out of memory saving file");
         }

         else
            last = last->next;

         buffer->last = last; /* avoid the need to rewrite every time */
         end_count = 0;
      }

      avail = (sizeof last->buffer) - end_count;
      if (avail > size)
         avail = size;

      memcpy(last->buffer + end_count, data, avail);
      end_count += avail;
      size -= avail;
      data += avail;
   }

   buffer->end_count = end_count;
}