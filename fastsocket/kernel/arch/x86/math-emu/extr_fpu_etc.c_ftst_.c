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
typedef  int u_char ;
typedef  int /*<<< orphan*/  FPU_REG ;

/* Variables and functions */
 int /*<<< orphan*/  EXCEPTION (int) ; 
 int EX_INTERNAL ; 
 int EX_Invalid ; 
 int EX_StackUnder ; 
 int /*<<< orphan*/  FPU_Special (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGN_POS ; 
 int SW_C0 ; 
 int SW_C2 ; 
 int SW_C3 ; 
#define  TAG_Empty 134 
#define  TAG_Special 133 
#define  TAG_Valid 132 
#define  TAG_Zero 131 
#define  TW_Denormal 130 
#define  TW_Infinity 129 
#define  TW_NaN 128 
 int /*<<< orphan*/  denormal_operand () ; 
 int /*<<< orphan*/  getsign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setcc (int) ; 

__attribute__((used)) static void ftst_(FPU_REG *st0_ptr, u_char st0tag)
{
	switch (st0tag) {
	case TAG_Zero:
		setcc(SW_C3);
		break;
	case TAG_Valid:
		if (getsign(st0_ptr) == SIGN_POS)
			setcc(0);
		else
			setcc(SW_C0);
		break;
	case TAG_Special:
		switch (FPU_Special(st0_ptr)) {
		case TW_Denormal:
			if (getsign(st0_ptr) == SIGN_POS)
				setcc(0);
			else
				setcc(SW_C0);
			if (denormal_operand() < 0) {
#ifdef PECULIAR_486
				/* This is weird! */
				if (getsign(st0_ptr) == SIGN_POS)
					setcc(SW_C3);
#endif /* PECULIAR_486 */
				return;
			}
			break;
		case TW_NaN:
			setcc(SW_C0 | SW_C2 | SW_C3);	/* Operand is not comparable */
			EXCEPTION(EX_Invalid);
			break;
		case TW_Infinity:
			if (getsign(st0_ptr) == SIGN_POS)
				setcc(0);
			else
				setcc(SW_C0);
			break;
		default:
			setcc(SW_C0 | SW_C2 | SW_C3);	/* Operand is not comparable */
			EXCEPTION(EX_INTERNAL | 0x14);
			break;
		}
		break;
	case TAG_Empty:
		setcc(SW_C0 | SW_C2 | SW_C3);
		EXCEPTION(EX_StackUnder);
		break;
	}
}