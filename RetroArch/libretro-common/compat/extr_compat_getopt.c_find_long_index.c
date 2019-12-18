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
 scalar_t__ is_long_option (char* const) ; 

__attribute__((used)) static int find_long_index(char * const *argv)
{
   int idx;
   for (idx = 0; argv[idx]; idx++)
   {
      if (is_long_option(argv[idx]))
         return idx;
   }

   return -1;
}