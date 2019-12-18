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
struct buffer {size_t read_count; size_t end_count; struct buffer_list* current; struct buffer_list* last; } ;
typedef  scalar_t__ png_size_t ;
typedef  size_t png_bytep ;

/* Variables and functions */
 int /*<<< orphan*/  INTERNAL_ERROR ; 
 int /*<<< orphan*/  USER_ERROR ; 
 int /*<<< orphan*/  display_log (struct display*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (size_t,scalar_t__,size_t) ; 

__attribute__((used)) static void
buffer_read(struct display *dp, struct buffer *bp, png_bytep data,
   png_size_t size)
{
   struct buffer_list *last = bp->current;
   size_t read_count = bp->read_count;

   while (size > 0)
   {
      size_t avail;

      if (last == NULL ||
         (last == bp->last && read_count >= bp->end_count))
      {
         display_log(dp, USER_ERROR, "file truncated (%lu bytes)",
            (unsigned long)size);
         /*NOTREACHED*/
         break;
      }

      else if (read_count >= sizeof last->buffer)
      {
         /* Move to the next buffer: */
         last = last->next;
         read_count = 0;
         bp->current = last; /* Avoid update outside the loop */

         /* And do a sanity check (the EOF case is caught above) */
         if (last == NULL)
         {
            display_log(dp, INTERNAL_ERROR, "damaged buffer list");
            /*NOTREACHED*/
            break;
         }
      }

      avail = (sizeof last->buffer) - read_count;
      if (avail > size)
         avail = size;

      memcpy(data, last->buffer + read_count, avail);
      read_count += avail;
      size -= avail;
      data += avail;
   }

   bp->read_count = read_count;
}