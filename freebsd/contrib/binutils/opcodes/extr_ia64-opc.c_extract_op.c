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
 unsigned int* dis_table ; 
 int extract_op_bits (int,int,int) ; 

__attribute__((used)) static int
extract_op (int op_pointer, int *opval, unsigned int *op)
{
  int oplen = 5;

  *op = dis_table[op_pointer];

  if ((*op) & 0x40)
    {
      opval[0] = extract_op_bits (op_pointer, oplen, 5);
      oplen += 5;
    }
  switch ((*op) & 0x30)
    {
    case 0x10:
      {
	opval[1] = extract_op_bits (op_pointer, oplen, 8);
	oplen += 8;
	opval[1] += op_pointer;
	break;
      }
    case 0x20:
      {
	opval[1] = extract_op_bits (op_pointer, oplen, 16);
	if (! (opval[1] & 32768))
	  {
	    opval[1] += op_pointer;
	  }
	oplen += 16;
	break;
      }
    case 0x30:
      {
	oplen--;
	opval[2] = extract_op_bits (op_pointer, oplen, 12);
	oplen += 12;
	opval[2] |= 32768;
	break;
      }
    }
  if (((*op) & 0x08) && (((*op) & 0x30) != 0x30))
    {
      opval[2] = extract_op_bits (op_pointer, oplen, 16);
      oplen += 16;
      if (! (opval[2] & 32768))
	{
	  opval[2] += op_pointer;
	}
    }
  return oplen;
}