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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct twl4030_keypad {int n_rows; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEYP_FULL_CODE_7_0 ; 
 int TWL4030_MAX_ROWS ; 
 int /*<<< orphan*/  twl4030_col_xlate (struct twl4030_keypad*,int /*<<< orphan*/ ) ; 
 int twl4030_kpread (struct twl4030_keypad*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int twl4030_read_kp_matrix_state(struct twl4030_keypad *kp, u16 *state)
{
	u8 new_state[TWL4030_MAX_ROWS];
	int row;
	int ret = twl4030_kpread(kp, new_state,
				 KEYP_FULL_CODE_7_0, kp->n_rows);
	if (ret >= 0)
		for (row = 0; row < kp->n_rows; row++)
			state[row] = twl4030_col_xlate(kp, new_state[row]);

	return ret;
}