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
struct input_polled_dev {int /*<<< orphan*/  input; struct aaedkbd* private; } ;
struct aaedkbd {unsigned int* kbdscan_state; scalar_t__* kbdscan_count; } ;

/* Variables and functions */
 int AAEC_GPIO_KSCAN ; 
 unsigned int AAED_EGPIO_KBD_SCAN ; 
 unsigned int AAED_EXT_GPIO ; 
 scalar_t__ KBDSCAN_STABLE_COUNT ; 
 int /*<<< orphan*/  KB_ACTIVATE_DELAY ; 
 unsigned int KB_COLS ; 
 int /*<<< orphan*/  aaedkbd_report_col (struct aaedkbd*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aaedkbd_poll(struct input_polled_dev *dev)
{
	struct aaedkbd *aaedkbd = dev->private;
	unsigned int col, rowd;

	col = 0;
	do {
		AAEC_GPIO_KSCAN = col + 8;
		udelay(KB_ACTIVATE_DELAY);
		rowd = AAED_EXT_GPIO & AAED_EGPIO_KBD_SCAN;

		if (rowd != aaedkbd->kbdscan_state[col]) {
			aaedkbd->kbdscan_count[col] = 0;
			aaedkbd->kbdscan_state[col] = rowd;
		} else if (++aaedkbd->kbdscan_count[col] >= KBDSCAN_STABLE_COUNT) {
			aaedkbd_report_col(aaedkbd, col, rowd);
			col++;
		}
	} while (col < KB_COLS);

	AAEC_GPIO_KSCAN = 0x07;
	input_sync(dev->input);
}