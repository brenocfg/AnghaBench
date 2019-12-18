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

/* Variables and functions */
 int CDB10 ; 
 scalar_t__ COMMAND_REG ; 
 scalar_t__ CONF_REG_1 ; 
 scalar_t__ CONF_REG_2 ; 
 scalar_t__ CONF_REG_3 ; 
 scalar_t__ CONF_REG_4 ; 
 scalar_t__ CONF_REG_5 ; 
 int EAN ; 
 int EPC ; 
 int FCLK ; 
 int FE ; 
 scalar_t__ FEATURE_EN ; 
 int FSCSI ; 
 int IDMRC ; 
 int IE ; 
 int NOOP ; 
 int QTE ; 
 int RESET_CHIP ; 
 int SCSI2 ; 
 scalar_t__ STP ; 
 scalar_t__ SYNC_OFFSET ; 
 int TBPA ; 
 scalar_t__ TOM ; 
 int WSE0 ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void sym53c416_init(int base, int scsi_id)
{
	outb(RESET_CHIP, base + COMMAND_REG);
	outb(NOOP, base + COMMAND_REG);
	outb(0x99, base + TOM); /* Time out of 250 ms */
	outb(0x05, base + STP);
	outb(0x00, base + SYNC_OFFSET);
	outb(EPC | scsi_id, base + CONF_REG_1);
	outb(FE | SCSI2 | TBPA, base + CONF_REG_2);
	outb(IDMRC | QTE | CDB10 | FSCSI | FCLK, base + CONF_REG_3);
	outb(0x83 | EAN, base + CONF_REG_4);
	outb(IE | WSE0, base + CONF_REG_5);
	outb(0, base + FEATURE_EN);
}