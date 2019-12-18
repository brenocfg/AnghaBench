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
struct onenand_chip {int options; int (* read_word ) (scalar_t__) ;int chipsize; scalar_t__ base; int /*<<< orphan*/  (* wait ) (struct mtd_info*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* command ) (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_word ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct mtd_info {int size; struct onenand_chip* priv; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLEXONENAND (struct onenand_chip*) ; 
 int /*<<< orphan*/  FL_LOCKING ; 
 int /*<<< orphan*/  ONENAND_CMD_UNLOCK ; 
 int /*<<< orphan*/  ONENAND_CMD_UNLOCK_ALL ; 
 int ONENAND_CTRL_ONGO ; 
 int ONENAND_HAS_UNLOCK_ALL ; 
 scalar_t__ ONENAND_IS_DDP (struct onenand_chip*) ; 
 scalar_t__ ONENAND_REG_CTRL_STATUS ; 
 scalar_t__ ONENAND_REG_START_BLOCK_ADDRESS ; 
 int ONENAND_SKIP_UNLOCK_CHECK ; 
 scalar_t__ onenand_check_lock_status (struct onenand_chip*) ; 
 int /*<<< orphan*/  onenand_do_lock_cmd (struct mtd_info*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int stub4 (scalar_t__) ; 

__attribute__((used)) static void onenand_unlock_all(struct mtd_info *mtd)
{
	struct onenand_chip *this = mtd->priv;
	loff_t ofs = 0;
	loff_t len = mtd->size;

	if (this->options & ONENAND_HAS_UNLOCK_ALL) {
		/* Set start block address */
		this->write_word(0, this->base + ONENAND_REG_START_BLOCK_ADDRESS);
		/* Write unlock command */
		this->command(mtd, ONENAND_CMD_UNLOCK_ALL, 0, 0);

		/* There's no return value */
		this->wait(mtd, FL_LOCKING);

		/* Sanity check */
		while (this->read_word(this->base + ONENAND_REG_CTRL_STATUS)
		    & ONENAND_CTRL_ONGO)
			continue;

		/* Don't check lock status */
		if (this->options & ONENAND_SKIP_UNLOCK_CHECK)
			return;

		/* Check lock status */
		if (onenand_check_lock_status(this))
			return;

		/* Workaround for all block unlock in DDP */
		if (ONENAND_IS_DDP(this) && !FLEXONENAND(this)) {
			/* All blocks on another chip */
			ofs = this->chipsize >> 1;
			len = this->chipsize >> 1;
		}
	}

	onenand_do_lock_cmd(mtd, ofs, len, ONENAND_CMD_UNLOCK);
}