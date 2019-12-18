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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  FPU_REG ;

/* Variables and functions */
#define  COMP_A_eq_B 131 
#define  COMP_A_gt_B 130 
#define  COMP_A_lt_B 129 
 int COMP_Denormal ; 
 int COMP_NaN ; 
#define  COMP_No_Comp 128 
 int /*<<< orphan*/  EXCEPTION (int) ; 
 int EX_INTERNAL ; 
 int EX_Invalid ; 
 int SW_C0 ; 
 int SW_C2 ; 
 int SW_C3 ; 
 int compare (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ denormal_operand () ; 
 int /*<<< orphan*/  setcc (int) ; 

int FPU_compare_st_data(FPU_REG const *loaded_data, u_char loaded_tag)
{
	int f = 0, c;

	c = compare(loaded_data, loaded_tag);

	if (c & COMP_NaN) {
		EXCEPTION(EX_Invalid);
		f = SW_C3 | SW_C2 | SW_C0;
	} else
		switch (c & 7) {
		case COMP_A_lt_B:
			f = SW_C0;
			break;
		case COMP_A_eq_B:
			f = SW_C3;
			break;
		case COMP_A_gt_B:
			f = 0;
			break;
		case COMP_No_Comp:
			f = SW_C3 | SW_C2 | SW_C0;
			break;
#ifdef PARANOID
		default:
			EXCEPTION(EX_INTERNAL | 0x121);
			f = SW_C3 | SW_C2 | SW_C0;
			break;
#endif /* PARANOID */
		}
	setcc(f);
	if (c & COMP_Denormal) {
		return denormal_operand() < 0;
	}
	return 0;
}