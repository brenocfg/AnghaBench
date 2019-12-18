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
typedef  int /*<<< orphan*/  png_const_bytep ;
typedef  scalar_t__* png_bytep ;
typedef  scalar_t__ png_byte ;

/* Variables and functions */
 int PNG_HANDLE_CHUNK_AS_DEFAULT ; 
 scalar_t__ memcmp (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int
add_one_chunk(png_bytep list, unsigned int count, png_const_bytep add, int keep)
{
   unsigned int i;

   /* Utility function: update the 'keep' state of a chunk if it is already in
    * the list, otherwise add it to the list.
    */
   for (i=0; i<count; ++i, list += 5)
   {
      if (memcmp(list, add, 4) == 0)
      {
         list[4] = (png_byte)keep;

         return count;
      }
   }

   if (keep != PNG_HANDLE_CHUNK_AS_DEFAULT)
   {
      ++count;
      memcpy(list, add, 4);
      list[4] = (png_byte)keep;
   }

   return count;
}