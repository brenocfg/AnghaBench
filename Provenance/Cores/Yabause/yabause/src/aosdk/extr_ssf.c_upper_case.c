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
 size_t strlen (char*) ; 
 char toupper (char) ; 

void upper_case(char * str)
{
   if (str)
   {
      size_t len = strlen(str);
      int i;

      for (i = 0; i < len; i++)
         str[i] = toupper(str[i]);
   }
}