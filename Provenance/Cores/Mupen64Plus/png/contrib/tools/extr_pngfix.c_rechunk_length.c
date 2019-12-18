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
typedef  struct IDAT_list {scalar_t__* lengths; unsigned int count; struct IDAT_list const* next; } const IDAT_list ;
struct IDAT {scalar_t__ idat_length; unsigned int idat_count; scalar_t__ idat_index; struct IDAT_list const* idat_list_tail; struct IDAT_list const* idat_cur; TYPE_1__* global; } ;
typedef  scalar_t__ png_uint_32 ;
struct TYPE_2__ {scalar_t__ idat_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static png_uint_32
rechunk_length(struct IDAT *idat, int start)
   /* Return the length for the next IDAT chunk, taking into account
    * rechunking.
    */
{
   png_uint_32 len = idat->global->idat_max;

   if (len == 0) /* use original chunk lengths */
   {
      const struct IDAT_list *cur;
      unsigned int count;

      if (start)
         return idat->idat_length; /* use the cache */

      /* Otherwise rechunk_length is called at the end of a chunk for the length
       * of the next one.
       */
      cur = idat->idat_cur;
      count = idat->idat_count;

      assert(idat->idat_index == idat->idat_length &&
         idat->idat_length == cur->lengths[count]);

      /* Return length of the *next* chunk */
      if (++count < cur->count)
         return cur->lengths[count];

      /* End of this list */
      assert(cur != idat->idat_list_tail);
      cur = cur->next;
      assert(cur != NULL && cur->count > 0);
      return cur->lengths[0];
   }

   else /* rechunking */
   {
      /* The chunk size is the lesser of file->idat_max and the number
       * of remaining bytes.
       */
      png_uint_32 have = idat->idat_length - idat->idat_index;

      if (len > have)
      {
         struct IDAT_list *cur = idat->idat_cur;
         unsigned int j = idat->idat_count+1; /* the next IDAT in the list */

         do
         {
            /* Add up the remaining bytes.  This can't overflow because the
             * individual lengths are always <= 0x7fffffff, so when we add two
             * of them overflow is not possible.
             */
            assert(cur != NULL);

            for (;;)
            {
               /* NOTE: IDAT_list::count here, not IDAT_list::length */
               for (; j < cur->count; ++j)
               {
                  have += cur->lengths[j];
                  if (len <= have)
                     return len;
               }

               /* If this was the end return the count of the available bytes */
               if (cur == idat->idat_list_tail)
                  return have;

               cur = cur->next;
               j = 0;
            }
         }
         while (len > have);
      }

      return len;
   }
}