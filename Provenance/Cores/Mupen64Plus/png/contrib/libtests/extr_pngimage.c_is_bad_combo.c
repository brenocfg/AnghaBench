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

/* Variables and functions */
 unsigned int ARRAY_SIZE (int**) ; 
 int** known_bad_combos ; 

__attribute__((used)) static int
is_bad_combo(int transforms)
{
   unsigned int i;

   for (i=0; i<ARRAY_SIZE(known_bad_combos); ++i)
   {
      int combo = known_bad_combos[i][0];

      if ((combo & transforms) == combo &&
         (transforms & known_bad_combos[i][1]) == 0)
         return 1;
   }

   return 0; /* combo is ok */
}