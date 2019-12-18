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
 int tolower (char const) ; 

__attribute__((used)) static int casencmp(const char *a, const char *b, size_t n)
{
   size_t i;

   for (i = 0; i < n; i++)
   {
      int a_lower = tolower(a[i]);
      int b_lower = tolower(b[i]);
      if (a_lower != b_lower)
         return a_lower - b_lower;
   }

   return 0;
}