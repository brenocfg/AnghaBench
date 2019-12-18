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
typedef  int png_uint_32 ;

/* Variables and functions */
 double L2INV ; 
 int /*<<< orphan*/  floor (double) ; 
 double log (unsigned int) ; 

__attribute__((used)) static png_uint_32 png_log8bit(unsigned x)
{
   if (x > 0)
      return (png_uint_32)floor(.5-log(x/255.)*L2INV);

   return 0xffffffff;
}