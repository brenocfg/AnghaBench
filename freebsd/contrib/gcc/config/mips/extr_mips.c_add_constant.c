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
struct mips16_constant_pool {scalar_t__ first; int highest_address; int insn_address; } ;
struct mips16_constant {int mode; int /*<<< orphan*/  label; struct mips16_constant* next; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ GET_MODE_SIZE (int) ; 
 int UNITS_PER_WORD ; 
 int /*<<< orphan*/  gen_label_rtx () ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static rtx
add_constant (struct mips16_constant_pool *pool,
	      rtx value, enum machine_mode mode)
{
  struct mips16_constant **p, *c;
  bool first_of_size_p;

  /* See whether the constant is already in the pool.  If so, return the
     existing label, otherwise leave P pointing to the place where the
     constant should be added.

     Keep the pool sorted in increasing order of mode size so that we can
     reduce the number of alignments needed.  */
  first_of_size_p = true;
  for (p = &pool->first; *p != 0; p = &(*p)->next)
    {
      if (mode == (*p)->mode && rtx_equal_p (value, (*p)->value))
	return (*p)->label;
      if (GET_MODE_SIZE (mode) < GET_MODE_SIZE ((*p)->mode))
	break;
      if (GET_MODE_SIZE (mode) == GET_MODE_SIZE ((*p)->mode))
	first_of_size_p = false;
    }

  /* In the worst case, the constant needed by the earliest instruction
     will end up at the end of the pool.  The entire pool must then be
     accessible from that instruction.

     When adding the first constant, set the pool's highest address to
     the address of the first out-of-range byte.  Adjust this address
     downwards each time a new constant is added.  */
  if (pool->first == 0)
    /* For pc-relative lw, addiu and daddiu instructions, the base PC value
       is the address of the instruction with the lowest two bits clear.
       The base PC value for ld has the lowest three bits clear.  Assume
       the worst case here.  */
    pool->highest_address = pool->insn_address - (UNITS_PER_WORD - 2) + 0x8000;
  pool->highest_address -= GET_MODE_SIZE (mode);
  if (first_of_size_p)
    /* Take into account the worst possible padding due to alignment.  */
    pool->highest_address -= GET_MODE_SIZE (mode) - 1;

  /* Create a new entry.  */
  c = (struct mips16_constant *) xmalloc (sizeof *c);
  c->value = value;
  c->mode = mode;
  c->label = gen_label_rtx ();
  c->next = *p;
  *p = c;

  return c->label;
}