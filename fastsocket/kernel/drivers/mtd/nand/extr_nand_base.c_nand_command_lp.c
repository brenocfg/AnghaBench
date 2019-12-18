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
struct nand_chip {int options; int chipsize; int (* read_byte ) (struct mtd_info*) ;int /*<<< orphan*/  chip_delay; int /*<<< orphan*/  dev_ready; int /*<<< orphan*/  (* cmd_ctrl ) (struct mtd_info*,int,int) ;} ;
struct mtd_info {scalar_t__ writesize; struct nand_chip* priv; } ;

/* Variables and functions */
 int NAND_ALE ; 
 int NAND_BUSWIDTH_16 ; 
 int NAND_CLE ; 
#define  NAND_CMD_CACHEDPROG 143 
#define  NAND_CMD_DEPLETE1 142 
#define  NAND_CMD_ERASE1 141 
#define  NAND_CMD_ERASE2 140 
 int NAND_CMD_NONE ; 
#define  NAND_CMD_PAGEPROG 139 
#define  NAND_CMD_READ0 138 
 unsigned int NAND_CMD_READOOB ; 
 int NAND_CMD_READSTART ; 
#define  NAND_CMD_RESET 137 
#define  NAND_CMD_RNDIN 136 
#define  NAND_CMD_RNDOUT 135 
 int NAND_CMD_RNDOUTSTART ; 
#define  NAND_CMD_SEQIN 134 
#define  NAND_CMD_STATUS 133 
#define  NAND_CMD_STATUS_ERROR 132 
#define  NAND_CMD_STATUS_ERROR0 131 
#define  NAND_CMD_STATUS_ERROR1 130 
#define  NAND_CMD_STATUS_ERROR2 129 
#define  NAND_CMD_STATUS_ERROR3 128 
 int NAND_CTRL_CHANGE ; 
 int NAND_NCE ; 
 int NAND_STATUS_READY ; 
 int /*<<< orphan*/  nand_wait_ready (struct mtd_info*) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,unsigned int,int) ; 
 int stub10 (struct mtd_info*) ; 
 int /*<<< orphan*/  stub11 (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  stub12 (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  stub13 (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  stub14 (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  stub7 (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  stub8 (struct mtd_info*,int const,int) ; 
 int /*<<< orphan*/  stub9 (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nand_command_lp(struct mtd_info *mtd, unsigned int command,
			    int column, int page_addr)
{
	register struct nand_chip *chip = mtd->priv;

	/* Emulate NAND_CMD_READOOB */
	if (command == NAND_CMD_READOOB) {
		column += mtd->writesize;
		command = NAND_CMD_READ0;
	}

	/* Command latch cycle */
	chip->cmd_ctrl(mtd, command & 0xff,
		       NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);

	if (column != -1 || page_addr != -1) {
		int ctrl = NAND_CTRL_CHANGE | NAND_NCE | NAND_ALE;

		/* Serially input address */
		if (column != -1) {
			/* Adjust columns for 16 bit buswidth */
			if (chip->options & NAND_BUSWIDTH_16)
				column >>= 1;
			chip->cmd_ctrl(mtd, column, ctrl);
			ctrl &= ~NAND_CTRL_CHANGE;
			chip->cmd_ctrl(mtd, column >> 8, ctrl);
		}
		if (page_addr != -1) {
			chip->cmd_ctrl(mtd, page_addr, ctrl);
			chip->cmd_ctrl(mtd, page_addr >> 8,
				       NAND_NCE | NAND_ALE);
			/* One more address cycle for devices > 128MiB */
			if (chip->chipsize > (128 << 20))
				chip->cmd_ctrl(mtd, page_addr >> 16,
					       NAND_NCE | NAND_ALE);
		}
	}
	chip->cmd_ctrl(mtd, NAND_CMD_NONE, NAND_NCE | NAND_CTRL_CHANGE);

	/*
	 * program and erase have their own busy handlers
	 * status, sequential in, and deplete1 need no delay
	 */
	switch (command) {

	case NAND_CMD_CACHEDPROG:
	case NAND_CMD_PAGEPROG:
	case NAND_CMD_ERASE1:
	case NAND_CMD_ERASE2:
	case NAND_CMD_SEQIN:
	case NAND_CMD_RNDIN:
	case NAND_CMD_STATUS:
	case NAND_CMD_DEPLETE1:
		return;

		/*
		 * read error status commands require only a short delay
		 */
	case NAND_CMD_STATUS_ERROR:
	case NAND_CMD_STATUS_ERROR0:
	case NAND_CMD_STATUS_ERROR1:
	case NAND_CMD_STATUS_ERROR2:
	case NAND_CMD_STATUS_ERROR3:
		udelay(chip->chip_delay);
		return;

	case NAND_CMD_RESET:
		if (chip->dev_ready)
			break;
		udelay(chip->chip_delay);
		chip->cmd_ctrl(mtd, NAND_CMD_STATUS,
			       NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);
		chip->cmd_ctrl(mtd, NAND_CMD_NONE,
			       NAND_NCE | NAND_CTRL_CHANGE);
		while (!(chip->read_byte(mtd) & NAND_STATUS_READY)) ;
		return;

	case NAND_CMD_RNDOUT:
		/* No ready / busy check necessary */
		chip->cmd_ctrl(mtd, NAND_CMD_RNDOUTSTART,
			       NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);
		chip->cmd_ctrl(mtd, NAND_CMD_NONE,
			       NAND_NCE | NAND_CTRL_CHANGE);
		return;

	case NAND_CMD_READ0:
		chip->cmd_ctrl(mtd, NAND_CMD_READSTART,
			       NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);
		chip->cmd_ctrl(mtd, NAND_CMD_NONE,
			       NAND_NCE | NAND_CTRL_CHANGE);

		/* This applies to read commands */
	default:
		/*
		 * If we don't have access to the busy pin, we apply the given
		 * command delay
		 */
		if (!chip->dev_ready) {
			udelay(chip->chip_delay);
			return;
		}
	}

	/* Apply this short delay always to ensure that we do wait tWB in
	 * any case on any machine. */
	ndelay(100);

	nand_wait_ready(mtd);
}