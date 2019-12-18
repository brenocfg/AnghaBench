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
struct TYPE_2__ {int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; } ;
struct nand_chip {int chip_delay; TYPE_1__* controller; TYPE_1__ hwcontrol; scalar_t__ scan_bbt; scalar_t__ verify_buf; scalar_t__ read_buf; scalar_t__ write_buf; scalar_t__ block_markbad; scalar_t__ block_bad; scalar_t__ read_word; scalar_t__ read_byte; scalar_t__ select_chip; int /*<<< orphan*/ * waitfunc; int /*<<< orphan*/ * cmdfunc; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ nand_block_bad ; 
 int /*<<< orphan*/ * nand_command ; 
 scalar_t__ nand_default_bbt ; 
 scalar_t__ nand_default_block_markbad ; 
 scalar_t__ nand_read_buf ; 
 scalar_t__ nand_read_buf16 ; 
 scalar_t__ nand_read_byte ; 
 scalar_t__ nand_read_byte16 ; 
 scalar_t__ nand_read_word ; 
 scalar_t__ nand_select_chip ; 
 scalar_t__ nand_verify_buf ; 
 scalar_t__ nand_verify_buf16 ; 
 int /*<<< orphan*/ * nand_wait ; 
 scalar_t__ nand_write_buf ; 
 scalar_t__ nand_write_buf16 ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nand_set_defaults(struct nand_chip *chip, int busw)
{
	/* check for proper chip_delay setup, set 20us if not */
	if (!chip->chip_delay)
		chip->chip_delay = 20;

	/* check, if a user supplied command function given */
	if (chip->cmdfunc == NULL)
		chip->cmdfunc = nand_command;

	/* check, if a user supplied wait function given */
	if (chip->waitfunc == NULL)
		chip->waitfunc = nand_wait;

	if (!chip->select_chip)
		chip->select_chip = nand_select_chip;
	if (!chip->read_byte)
		chip->read_byte = busw ? nand_read_byte16 : nand_read_byte;
	if (!chip->read_word)
		chip->read_word = nand_read_word;
	if (!chip->block_bad)
		chip->block_bad = nand_block_bad;
	if (!chip->block_markbad)
		chip->block_markbad = nand_default_block_markbad;
	if (!chip->write_buf)
		chip->write_buf = busw ? nand_write_buf16 : nand_write_buf;
	if (!chip->read_buf)
		chip->read_buf = busw ? nand_read_buf16 : nand_read_buf;
	if (!chip->verify_buf)
		chip->verify_buf = busw ? nand_verify_buf16 : nand_verify_buf;
	if (!chip->scan_bbt)
		chip->scan_bbt = nand_default_bbt;

	if (!chip->controller) {
		chip->controller = &chip->hwcontrol;
		spin_lock_init(&chip->controller->lock);
		init_waitqueue_head(&chip->controller->wq);
	}

}