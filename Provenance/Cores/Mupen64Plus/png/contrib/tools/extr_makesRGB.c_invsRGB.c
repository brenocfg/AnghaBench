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
typedef  int /*<<< orphan*/  png_uint_16 ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  finvsRGB (unsigned int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 unsigned int nearbyint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

png_uint_16
invsRGB(unsigned int i)
{
   unsigned int x = nearbyint(finvsRGB(i));

   if (x > 65535)
   {
      fprintf(stderr, "invsRGB(%u) overflows to %u\n", i, x);
      exit(1);
   }

   return (png_uint_16)x;
}