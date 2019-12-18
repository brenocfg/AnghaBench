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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
#define  BImode 136 
#define  DFmode 135 
#define  DImode 134 
#define  HImode 133 
#define  QImode 132 
#define  SFmode 131 
#define  SImode 130 
 int SPEC_MODE_INVALID ; 
#define  TImode 129 
#define  XFmode 128 

__attribute__((used)) static int
ia64_mode_to_int (enum machine_mode mode)
{
  switch (mode)
    {
    case BImode: return 0; /* SPEC_MODE_FIRST  */
    case QImode: return 1; /* SPEC_MODE_FOR_EXTEND_FIRST  */
    case HImode: return 2;
    case SImode: return 3; /* SPEC_MODE_FOR_EXTEND_LAST  */
    case DImode: return 4;
    case SFmode: return 5;
    case DFmode: return 6;
    case XFmode: return 7;
    case TImode:
      /* ??? This mode needs testing.  Bypasses for ldfp8 instruction are not
	 mentioned in itanium[12].md.  Predicate fp_register_operand also
	 needs to be defined.  Bottom line: better disable for now.  */
      return SPEC_MODE_INVALID;
    default:     return SPEC_MODE_INVALID;
    }
}