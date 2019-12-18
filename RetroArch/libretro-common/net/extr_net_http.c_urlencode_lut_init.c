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
 scalar_t__ isalnum (unsigned int) ; 
 unsigned int* urlencode_lut ; 
 int urlencode_lut_inited ; 

void urlencode_lut_init(void)
{
   unsigned i;

   urlencode_lut_inited = true;

   for (i = 0; i < 256; i++)
   {
      urlencode_lut[i] = isalnum(i) || i == '*' || i == '-' || i == '.' || i == '_' || i == '/' ? i : 0;
   }
}