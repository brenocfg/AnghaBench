#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct aaedkbd {int /*<<< orphan*/ * keycode; TYPE_1__* poll_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 unsigned int KB_ROWMASK (unsigned int) ; 
 unsigned int KB_ROWS ; 
 unsigned int SCANCODE (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void aaedkbd_report_col(struct aaedkbd *aaedkbd,
				unsigned int col, unsigned int rowd)
{
	unsigned int scancode, pressed;
	unsigned int row;

	for (row = 0; row < KB_ROWS; row++) {
		scancode = SCANCODE(row, col);
		pressed = rowd & KB_ROWMASK(row);

		input_report_key(aaedkbd->poll_dev->input,
				 aaedkbd->keycode[scancode], pressed);
	}
}