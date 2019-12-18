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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int PARITY_MASK ; 
 int /*<<< orphan*/  SCSI_Cntl_port ; 
 int /*<<< orphan*/  SCSI_Mode_Cntl_port ; 
 int /*<<< orphan*/  TMC_Cntl_port ; 
 scalar_t__ chip ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 scalar_t__ tmc18c30 ; 
 scalar_t__ tmc18c50 ; 

__attribute__((used)) static void fd_mcs_make_bus_idle(struct Scsi_Host *shpnt)
{
	outb(0, SCSI_Cntl_port);
	outb(0, SCSI_Mode_Cntl_port);
	if (chip == tmc18c50 || chip == tmc18c30)
		outb(0x21 | PARITY_MASK, TMC_Cntl_port);	/* Clear forced intr. */
	else
		outb(0x01 | PARITY_MASK, TMC_Cntl_port);
}