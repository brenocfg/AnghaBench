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
 int PREFIX_CS ; 
 int PREFIX_DS ; 
 int PREFIX_ES ; 
 int PREFIX_FS ; 
 int PREFIX_GS ; 
 int PREFIX_SS ; 
 int /*<<< orphan*/  append_seg () ; 
 int /*<<< orphan*/  b_mode ; 
 int* codep ; 
 int /*<<< orphan*/  intel_operand_size (int /*<<< orphan*/ ,int) ; 
 scalar_t__ intel_syntax ; 
 int prefixes ; 
 int /*<<< orphan*/  ptr_reg (int,int) ; 
 int /*<<< orphan*/  v_mode ; 
 int /*<<< orphan*/  z_mode ; 

__attribute__((used)) static void
OP_DSreg (int code, int sizeflag)
{
  if (intel_syntax)
    {
      switch (codep[-1])
	{
	case 0x6f:	/* outsw/outsl */
	  intel_operand_size (z_mode, sizeflag);
	  break;
	case 0xa5:	/* movsw/movsl/movsq */
	case 0xa7:	/* cmpsw/cmpsl/cmpsq */
	case 0xad:	/* lodsw/lodsl/lodsq */
	  intel_operand_size (v_mode, sizeflag);
	  break;
	default:
	  intel_operand_size (b_mode, sizeflag);
	}
    }
  if ((prefixes
       & (PREFIX_CS
	  | PREFIX_DS
	  | PREFIX_SS
	  | PREFIX_ES
	  | PREFIX_FS
	  | PREFIX_GS)) == 0)
    prefixes |= PREFIX_DS;
  append_seg ();
  ptr_reg (code, sizeflag);
}