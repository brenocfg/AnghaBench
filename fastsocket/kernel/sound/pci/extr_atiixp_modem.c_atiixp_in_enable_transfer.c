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
 unsigned int ATI_REG_CMD_MODEM_RECEIVE_EN ; 
 int /*<<< orphan*/  CMD ; 
 unsigned int atiixp_read (struct atiixp_modem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_update (struct atiixp_modem*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_write (struct atiixp_modem*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void atiixp_in_enable_transfer(struct atiixp_modem *chip, int on)
{
	if (on) {
		unsigned int data = atiixp_read(chip, CMD);
		if (! (data & ATI_REG_CMD_MODEM_RECEIVE_EN)) {
			data |= ATI_REG_CMD_MODEM_RECEIVE_EN;
			atiixp_write(chip, CMD, data);
		}
	} else
		atiixp_update(chip, CMD, ATI_REG_CMD_MODEM_RECEIVE_EN, 0);
}