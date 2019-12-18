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
struct onenand_chip {int chipsize; int page_shift; scalar_t__ base; int /*<<< orphan*/  erase_shift; } ;

/* Variables and functions */
 int ONENAND_BSA_DATARAM1 ; 
 int ONENAND_BSA_SHIFT ; 
#define  ONENAND_CMD_BUFFERRAM 132 
 int ONENAND_CMD_ERASE ; 
#define  ONENAND_CMD_LOCK 131 
#define  ONENAND_CMD_LOCK_TIGHT 130 
#define  ONENAND_CMD_UNLOCK 129 
#define  ONENAND_CMD_UNLOCK_ALL 128 
 int ONENAND_DDP_SHIFT ; 
 int ONENAND_FPA_SHIFT ; 
 scalar_t__ ONENAND_REG_START_ADDRESS1 ; 
 scalar_t__ ONENAND_REG_START_ADDRESS8 ; 
 scalar_t__ ONENAND_REG_START_BUFFER ; 
 unsigned long onenand_addr (struct onenand_chip*,int) ; 
 int /*<<< orphan*/  onenand_data_handle (struct onenand_chip*,int,int,unsigned long) ; 
 int /*<<< orphan*/  onenand_lock_handle (struct onenand_chip*,int) ; 
 int /*<<< orphan*/  onenand_update_interrupt (struct onenand_chip*,int) ; 
 scalar_t__ readw (scalar_t__) ; 

__attribute__((used)) static void onenand_command_handle(struct onenand_chip *this, int cmd)
{
	unsigned long offset = 0;
	int block = -1, page = -1, bufferram = -1;
	int dataram = 0;

	switch (cmd) {
	case ONENAND_CMD_UNLOCK:
	case ONENAND_CMD_LOCK:
	case ONENAND_CMD_LOCK_TIGHT:
	case ONENAND_CMD_UNLOCK_ALL:
		onenand_lock_handle(this, cmd);
		break;

	case ONENAND_CMD_BUFFERRAM:
		/* Do nothing */
		return;

	default:
		block = (int) readw(this->base + ONENAND_REG_START_ADDRESS1);
		if (block & (1 << ONENAND_DDP_SHIFT)) {
			block &= ~(1 << ONENAND_DDP_SHIFT);
			/* The half of chip block */
			block += this->chipsize >> (this->erase_shift + 1);
		}
		if (cmd == ONENAND_CMD_ERASE)
			break;

		page = (int) readw(this->base + ONENAND_REG_START_ADDRESS8);
		page = (page >> ONENAND_FPA_SHIFT);
		bufferram = (int) readw(this->base + ONENAND_REG_START_BUFFER);
		bufferram >>= ONENAND_BSA_SHIFT;
		bufferram &= ONENAND_BSA_DATARAM1;
		dataram = (bufferram == ONENAND_BSA_DATARAM1) ? 1 : 0;
		break;
	}

	if (block != -1)
		offset = onenand_addr(this, block);

	if (page != -1)
		offset += page << this->page_shift;

	onenand_data_handle(this, cmd, dataram, offset);

	onenand_update_interrupt(this, cmd);
}