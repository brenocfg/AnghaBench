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
typedef  int /*<<< orphan*/  png_const_structp ;
typedef  int png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static unsigned int
bit_size(png_const_structp pp, png_byte colour_type, png_byte bit_depth)
{
   switch (colour_type)
   {
      default: png_error(pp, "invalid color type");

      case 0:  return bit_depth;

      case 2:  return 3*bit_depth;

      case 3:  return bit_depth;

      case 4:  return 2*bit_depth;

      case 6:  return 4*bit_depth;
   }
}