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
struct TYPE_3__ {int* buffer; } ;
typedef  TYPE_1__ mep_insn ;

/* Variables and functions */
 int CGEN_INSN_OPTIONAL_CP_INSN ; 
 int CGEN_INSN_OPTIONAL_DEBUG_INSN ; 
 int CGEN_INSN_OPTIONAL_DIV_INSN ; 
 int CGEN_INSN_OPTIONAL_MUL_INSN ; 
 int MEP_OMASK ; 
 scalar_t__ allow_disabled_registers ; 
 int /*<<< orphan*/  as_bad (char*) ; 
 scalar_t__ target_big_endian ; 

__attribute__((used)) static void
mep_check_for_disabled_registers (mep_insn *insn)
{
  static int initted = 0;
  static int has_mul_div = 0;
  static int has_cop = 0;
  static int has_debug = 0;
  unsigned int b, r;

  if (allow_disabled_registers)
    return;

#if !CGEN_INT_INSN_P
  if (target_big_endian)
    b = insn->buffer[0] * 256 + insn->buffer[1];
  else
    b = insn->buffer[1] * 256 + insn->buffer[0];
#else
  b = insn->buffer[0];
#endif

  if ((b & 0xfffff00e) == 0x7008 /* stc */
      || (b & 0xfffff00e) == 0x700a /* ldc */)
    {
      if (!initted)
	{
	  initted = 1;
	  if ((MEP_OMASK & (1 << CGEN_INSN_OPTIONAL_MUL_INSN))
	      || (MEP_OMASK & (1 << CGEN_INSN_OPTIONAL_DIV_INSN)))
	    has_mul_div = 1;
	  if (MEP_OMASK & (1 << CGEN_INSN_OPTIONAL_DEBUG_INSN))
	    has_debug = 1;
	  if (MEP_OMASK & (1 << CGEN_INSN_OPTIONAL_CP_INSN))
	    has_cop = 1;
	}

      r = ((b & 0x00f0) >> 4) | ((b & 0x0001) << 4);
      switch (r)
	{
	case 7: /* $hi */
	case 8: /* $lo */
	  if (!has_mul_div)
	    as_bad ("$hi and $lo are disabled when MUL and DIV are off");
	  break;
	case 12: /* $mb0 */
	case 13: /* $me0 */
	case 14: /* $mb1 */
	case 15: /* $me1 */
	  if (!has_cop)
	    as_bad ("$mb0, $me0, $mb1, and $me1 are disabled when COP is off");
	  break;
	case 24: /* $dbg */
	case 25: /* $depc */
	  if (!has_debug)
	    as_bad ("$dbg and $depc are disabled when DEBUG is off");
	  break;
	}
    }
}