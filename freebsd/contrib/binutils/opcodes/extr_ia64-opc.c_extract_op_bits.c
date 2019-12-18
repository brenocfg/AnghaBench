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
 int* dis_table ; 

__attribute__((used)) static int
extract_op_bits (int op_pointer, int bitoffset, int bits)
{
  int res = 0;

  op_pointer += (bitoffset / 8);

  if (bitoffset % 8)
    {
      unsigned int op = dis_table[op_pointer++];
      int numb = 8 - (bitoffset % 8);
      int mask = (1 << numb) - 1;
      int bata = (bits < numb) ? bits : numb;
      int delta = numb - bata;

      res = (res << bata) | ((op & mask) >> delta);
      bitoffset += bata;
      bits -= bata;
    }
  while (bits >= 8)
    {
      res = (res << 8) | (dis_table[op_pointer++] & 255);
      bits -= 8;
    }
  if (bits > 0)
    {
      unsigned int op = (dis_table[op_pointer++] & 255);
      res = (res << bits) | (op >> (8 - bits));
    }
  return res;
}