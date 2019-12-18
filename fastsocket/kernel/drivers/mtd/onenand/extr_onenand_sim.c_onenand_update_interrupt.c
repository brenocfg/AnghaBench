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
struct onenand_chip {scalar_t__ base; } ;

/* Variables and functions */
#define  ONENAND_CMD_ERASE 133 
#define  ONENAND_CMD_PROG 132 
#define  ONENAND_CMD_PROGOOB 131 
#define  ONENAND_CMD_READ 130 
#define  ONENAND_CMD_READOOB 129 
#define  ONENAND_CMD_RESET 128 
 int ONENAND_INT_ERASE ; 
 int ONENAND_INT_MASTER ; 
 int ONENAND_INT_READ ; 
 int ONENAND_INT_RESET ; 
 int ONENAND_INT_WRITE ; 
 scalar_t__ ONENAND_REG_INTERRUPT ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void onenand_update_interrupt(struct onenand_chip *this, int cmd)
{
	int interrupt = ONENAND_INT_MASTER;

	switch (cmd) {
	case ONENAND_CMD_READ:
	case ONENAND_CMD_READOOB:
		interrupt |= ONENAND_INT_READ;
		break;

	case ONENAND_CMD_PROG:
	case ONENAND_CMD_PROGOOB:
		interrupt |= ONENAND_INT_WRITE;
		break;

	case ONENAND_CMD_ERASE:
		interrupt |= ONENAND_INT_ERASE;
		break;

	case ONENAND_CMD_RESET:
		interrupt |= ONENAND_INT_RESET;
		break;

	default:
		break;
	}

	writew(interrupt, this->base + ONENAND_REG_INTERRUPT);
}