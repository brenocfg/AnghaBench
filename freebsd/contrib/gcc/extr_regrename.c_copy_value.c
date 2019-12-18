#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct value_data {TYPE_1__* e; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {size_t mode; unsigned int next_regno; int /*<<< orphan*/  oldest_regno; } ;

/* Variables and functions */
 scalar_t__ BYTES_BIG_ENDIAN ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_SIZE (size_t) ; 
 unsigned int HARD_FRAME_POINTER_REGNUM ; 
 unsigned int INVALID_REGNUM ; 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 unsigned int STACK_POINTER_REGNUM ; 
 scalar_t__ UNITS_PER_WORD ; 
 size_t VOIDmode ; 
 scalar_t__ WORDS_BIG_ENDIAN ; 
 scalar_t__* fixed_regs ; 
 scalar_t__ frame_pointer_needed ; 
 scalar_t__* global_regs ; 
 unsigned int** hard_regno_nregs ; 
 int /*<<< orphan*/  set_value_regno (unsigned int,size_t,struct value_data*) ; 
 int /*<<< orphan*/  validate_value_data (struct value_data*) ; 

__attribute__((used)) static void
copy_value (rtx dest, rtx src, struct value_data *vd)
{
  unsigned int dr = REGNO (dest);
  unsigned int sr = REGNO (src);
  unsigned int dn, sn;
  unsigned int i;

  /* ??? At present, it's possible to see noop sets.  It'd be nice if
     this were cleaned up beforehand...  */
  if (sr == dr)
    return;

  /* Do not propagate copies to the stack pointer, as that can leave
     memory accesses with no scheduling dependency on the stack update.  */
  if (dr == STACK_POINTER_REGNUM)
    return;

  /* Likewise with the frame pointer, if we're using one.  */
  if (frame_pointer_needed && dr == HARD_FRAME_POINTER_REGNUM)
    return;

  /* Do not propagate copies to fixed or global registers, patterns
     can be relying to see particular fixed register or users can
     expect the chosen global register in asm.  */
  if (fixed_regs[dr] || global_regs[dr])
    return;

  /* If SRC and DEST overlap, don't record anything.  */
  dn = hard_regno_nregs[dr][GET_MODE (dest)];
  sn = hard_regno_nregs[sr][GET_MODE (dest)];
  if ((dr > sr && dr < sr + sn)
      || (sr > dr && sr < dr + dn))
    return;

  /* If SRC had no assigned mode (i.e. we didn't know it was live)
     assign it now and assume the value came from an input argument
     or somesuch.  */
  if (vd->e[sr].mode == VOIDmode)
    set_value_regno (sr, vd->e[dr].mode, vd);

  /* If we are narrowing the input to a smaller number of hard regs,
     and it is in big endian, we are really extracting a high part.
     Since we generally associate a low part of a value with the value itself,
     we must not do the same for the high part.
     Note we can still get low parts for the same mode combination through
     a two-step copy involving differently sized hard regs.
     Assume hard regs fr* are 32 bits bits each, while r* are 64 bits each:
     (set (reg:DI r0) (reg:DI fr0))
     (set (reg:SI fr2) (reg:SI r0))
     loads the low part of (reg:DI fr0) - i.e. fr1 - into fr2, while:
     (set (reg:SI fr2) (reg:SI fr0))
     loads the high part of (reg:DI fr0) into fr2.

     We can't properly represent the latter case in our tables, so don't
     record anything then.  */
  else if (sn < (unsigned int) hard_regno_nregs[sr][vd->e[sr].mode]
	   && (GET_MODE_SIZE (vd->e[sr].mode) > UNITS_PER_WORD
	       ? WORDS_BIG_ENDIAN : BYTES_BIG_ENDIAN))
    return;

  /* If SRC had been assigned a mode narrower than the copy, we can't
     link DEST into the chain, because not all of the pieces of the
     copy came from oldest_regno.  */
  else if (sn > (unsigned int) hard_regno_nregs[sr][vd->e[sr].mode])
    return;

  /* Link DR at the end of the value chain used by SR.  */

  vd->e[dr].oldest_regno = vd->e[sr].oldest_regno;

  for (i = sr; vd->e[i].next_regno != INVALID_REGNUM; i = vd->e[i].next_regno)
    continue;
  vd->e[i].next_regno = dr;

#ifdef ENABLE_CHECKING
  validate_value_data (vd);
#endif
}