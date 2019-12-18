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
struct input_dev {int dummy; } ;
struct bfin_rot {int /*<<< orphan*/  rel_code; int /*<<< orphan*/  down_key; int /*<<< orphan*/  up_key; struct input_dev* input; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  report_key_event (struct input_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void report_rotary_event(struct bfin_rot *rotary, int delta)
{
	struct input_dev *input = rotary->input;

	if (rotary->up_key) {
		report_key_event(input,
				 delta > 0 ? rotary->up_key : rotary->down_key);
	} else {
		input_report_rel(input, rotary->rel_code, delta);
		input_sync(input);
	}
}