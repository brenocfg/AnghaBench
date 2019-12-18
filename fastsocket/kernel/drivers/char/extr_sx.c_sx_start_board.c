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
struct sx_board {int irq; scalar_t__ eisa_base; } ;

/* Variables and functions */
 scalar_t__ IS_EISA_BOARD (struct sx_board*) ; 
 scalar_t__ IS_SI1_BOARD (struct sx_board*) ; 
 scalar_t__ IS_SX_BOARD (struct sx_board*) ; 
 int /*<<< orphan*/  SI1_ISA_INTCL ; 
 int /*<<< orphan*/  SI1_ISA_RESET_CLEAR ; 
 int /*<<< orphan*/  SI2_EISA_OFF ; 
 int /*<<< orphan*/  SI2_EISA_VAL ; 
 int /*<<< orphan*/  SI2_ISA_INTCLEAR ; 
 int /*<<< orphan*/  SI2_ISA_INTCLEAR_SET ; 
 int /*<<< orphan*/  SI2_ISA_RESET ; 
 int /*<<< orphan*/  SI2_ISA_RESET_CLEAR ; 
 int /*<<< orphan*/  SX_CONFIG ; 
 int /*<<< orphan*/  SX_CONF_BUSEN ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  write_sx_byte (struct sx_board*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sx_start_board(struct sx_board *board)
{
	if (IS_SX_BOARD(board)) {
		write_sx_byte(board, SX_CONFIG, SX_CONF_BUSEN);
	} else if (IS_EISA_BOARD(board)) {
		write_sx_byte(board, SI2_EISA_OFF, SI2_EISA_VAL);
		outb((board->irq << 4) | 4, board->eisa_base + 0xc02);
	} else if (IS_SI1_BOARD(board)) {
		write_sx_byte(board, SI1_ISA_RESET_CLEAR, 0);
		write_sx_byte(board, SI1_ISA_INTCL, 0);
	} else {
		/* Don't bug me about the clear_set. 
		   I haven't the foggiest idea what it's about -- REW */
		write_sx_byte(board, SI2_ISA_RESET, SI2_ISA_RESET_CLEAR);
		write_sx_byte(board, SI2_ISA_INTCLEAR, SI2_ISA_INTCLEAR_SET);
	}
	return 1;
}