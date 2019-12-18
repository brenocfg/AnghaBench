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
typedef  unsigned int insn32 ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 unsigned int HI_LOW_ORDER ; 
 unsigned int LOW_HI_ORDER ; 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static insn32
insert_thumb_branch (insn32 br_insn, int rel_off)
{
  unsigned int low_bits;
  unsigned int high_bits;

  BFD_ASSERT ((rel_off & 1) != 1);

  rel_off >>= 1;                              /* Half word aligned address.  */
  low_bits = rel_off & 0x000007FF;            /* The bottom 11 bits.  */
  high_bits = (rel_off >> 11) & 0x000007FF;   /* The top 11 bits.  */

  if ((br_insn & LOW_HI_ORDER) == LOW_HI_ORDER)
    br_insn = LOW_HI_ORDER | (low_bits << 16) | high_bits;
  else if ((br_insn & HI_LOW_ORDER) == HI_LOW_ORDER)
    br_insn = HI_LOW_ORDER | (high_bits << 16) | low_bits;
  else
    /* FIXME: the BFD library should never abort except for internal errors
       - it should return an error status.  */
    abort (); /* Error - not a valid branch instruction form.  */

  return br_insn;
}