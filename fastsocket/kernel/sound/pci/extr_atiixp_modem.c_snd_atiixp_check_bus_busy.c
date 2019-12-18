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
struct atiixp_modem {int dummy; } ;

/* Variables and functions */
 int ATI_REG_CMD_MODEM_RECEIVE_EN ; 
 int ATI_REG_CMD_MODEM_SEND1_EN ; 
 unsigned int ATI_REG_IER_MODEM_SET_BUS_BUSY ; 
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  IER ; 
 int atiixp_read (struct atiixp_modem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_update (struct atiixp_modem*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void snd_atiixp_check_bus_busy(struct atiixp_modem *chip)
{
	unsigned int bus_busy;
	if (atiixp_read(chip, CMD) & (ATI_REG_CMD_MODEM_SEND1_EN |
				      ATI_REG_CMD_MODEM_RECEIVE_EN))
		bus_busy = ATI_REG_IER_MODEM_SET_BUS_BUSY;
	else
		bus_busy = 0;
	atiixp_update(chip, IER, ATI_REG_IER_MODEM_SET_BUS_BUSY, bus_busy);
}