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
typedef  int u16 ;
struct twl4030_keypad {int n_rows; int* kp_state; int n_cols; int /*<<< orphan*/ * keymap; int /*<<< orphan*/  dbg_dev; struct input_dev* input; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  new_state ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int MATRIX_SCAN_CODE (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int TWL4030_MAX_ROWS ; 
 int /*<<< orphan*/  TWL4030_ROW_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,char*) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ twl4030_is_in_ghost_state (struct twl4030_keypad*,int*) ; 
 int twl4030_read_kp_matrix_state (struct twl4030_keypad*,int*) ; 

__attribute__((used)) static void twl4030_kp_scan(struct twl4030_keypad *kp, bool release_all)
{
	struct input_dev *input = kp->input;
	u16 new_state[TWL4030_MAX_ROWS];
	int col, row;

	if (release_all)
		memset(new_state, 0, sizeof(new_state));
	else {
		/* check for any changes */
		int ret = twl4030_read_kp_matrix_state(kp, new_state);

		if (ret < 0)	/* panic ... */
			return;

		if (twl4030_is_in_ghost_state(kp, new_state))
			return;
	}

	/* check for changes and print those */
	for (row = 0; row < kp->n_rows; row++) {
		int changed = new_state[row] ^ kp->kp_state[row];

		if (!changed)
			continue;

		for (col = 0; col < kp->n_cols; col++) {
			int code;

			if (!(changed & (1 << col)))
				continue;

			dev_dbg(kp->dbg_dev, "key [%d:%d] %s\n", row, col,
				(new_state[row] & (1 << col)) ?
				"press" : "release");

			code = MATRIX_SCAN_CODE(row, col, TWL4030_ROW_SHIFT);
			input_event(input, EV_MSC, MSC_SCAN, code);
			input_report_key(input, kp->keymap[code],
					 new_state[row] & (1 << col));
		}
		kp->kp_state[row] = new_state[row];
	}
	input_sync(input);
}