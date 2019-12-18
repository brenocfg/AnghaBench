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
struct sx_board {int dummy; } ;

/* Variables and functions */
 int TIMEOUT_1 ; 
 int TIMEOUT_2 ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int read_sx_byte (struct sx_board*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sx_busy_wait_neq(struct sx_board *board,
		int offset, int mask, int badval)
{
	int i;

	func_enter();

	for (i = 0; i < TIMEOUT_1; i++)
		if ((read_sx_byte(board, offset) & mask) != badval) {
			func_exit();
			return 1;
		}

	for (i = 0; i < TIMEOUT_2; i++) {
		if ((read_sx_byte(board, offset) & mask) != badval) {
			func_exit();
			return 1;
		}
		udelay(1);
	}

	func_exit();
	return 0;
}