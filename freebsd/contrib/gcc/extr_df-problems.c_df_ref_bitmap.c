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
typedef  scalar_t__ bitmap ;

/* Variables and functions */
 scalar_t__ BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_set_bit (scalar_t__,unsigned int) ; 

__attribute__((used)) static inline bitmap
df_ref_bitmap (bitmap *maps, unsigned int regno, int start, int count)
{
  bitmap ids = maps[regno];
  if (!ids)
    {
      unsigned int i;
      unsigned int end = start + count;;
      ids = BITMAP_ALLOC (NULL);
      maps[regno] = ids;
      for (i = start; i < end; i++)
	bitmap_set_bit (ids, i);
    }
  return ids;
}