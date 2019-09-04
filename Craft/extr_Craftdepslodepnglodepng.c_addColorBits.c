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

__attribute__((used)) static void addColorBits(unsigned char* out, size_t index, unsigned bits, unsigned in)
{
  /*p = the partial index in the byte, e.g. with 4 palettebits it is 0 for first half or 1 for second half*/
  unsigned p = index % (8 / bits);
  in &= (1 << bits) - 1; /*filter out any other bits of the input value*/
  in = in << (bits * (8 / bits - p - 1));
  if(p == 0) out[index * bits / 8] = in;
  else out[index * bits / 8] |= in;
}