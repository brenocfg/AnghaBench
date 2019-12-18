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

__attribute__((used)) static char
type_char(png_uint_32 v)
{
   /* In fact because chunk::chunk_type is validated prior to any call to this
    * function it will always return a-zA-Z, but the extra codes are just there
    * to help in finding internal (programming) errors.  Note that the code only
    * ever considers the low 7 bits of the value (so it is not necessary for the
    * type_name function to mask of the byte.)
    */
   if (v & 32)
      return "!abcdefghijklmnopqrstuvwxyz56789"[(v-96)&31];

   else
      return "@ABCDEFGHIJKLMNOPQRSTUVWXYZ01234"[(v-64)&31];
}