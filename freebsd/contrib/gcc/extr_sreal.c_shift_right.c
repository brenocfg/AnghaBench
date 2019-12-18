#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uhwi ;
struct TYPE_3__ {scalar_t__ exp; int sig_hi; int sig_lo; int sig; } ;
typedef  TYPE_1__ sreal ;

/* Variables and functions */
 int SREAL_BITS ; 
 scalar_t__ SREAL_MAX_EXP ; 
 int SREAL_PART_BITS ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static inline void
shift_right (sreal *x, int s)
{
  gcc_assert (s > 0);
  gcc_assert (s <= SREAL_BITS);
  /* Exponent should never be so large because shift_right is used only by
     sreal_add and sreal_sub ant thus the number cannot be shifted out from
     exponent range.  */
  gcc_assert (x->exp + s <= SREAL_MAX_EXP);

  x->exp += s;

#if SREAL_PART_BITS < 32
  if (s > SREAL_PART_BITS)
    {
      s -= SREAL_PART_BITS;
      x->sig_hi += (uhwi) 1 << (s - 1);
      x->sig_lo = x->sig_hi >> s;
      x->sig_hi = 0;
    }
  else
    {
      x->sig_lo += (uhwi) 1 << (s - 1);
      if (x->sig_lo & ((uhwi) 1 << SREAL_PART_BITS))
	{
	  x->sig_hi++;
	  x->sig_lo -= (uhwi) 1 << SREAL_PART_BITS;
	}
      x->sig_lo >>= s;
      x->sig_lo |= (x->sig_hi & (((uhwi) 1 << s) - 1)) << (SREAL_PART_BITS - s);
      x->sig_hi >>= s;
    }
#else
  x->sig += (uhwi) 1 << (s - 1);
  x->sig >>= s;
#endif
}