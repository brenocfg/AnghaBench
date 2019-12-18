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
typedef  int u32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  fsib; int /*<<< orphan*/  fsia; } ;

/* Variables and functions */
 int INT_A_OUT ; 
 int INT_B_OUT ; 
 int /*<<< orphan*/  INT_ST ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SOFT_RST ; 
 int /*<<< orphan*/  fsi_data_push (int /*<<< orphan*/ *) ; 
 int fsi_master_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_master_write (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* master ; 

__attribute__((used)) static irqreturn_t fsi_interrupt(int irq, void *data)
{
	u32 status = fsi_master_read(SOFT_RST) & ~0x00000010;
	u32 int_st = fsi_master_read(INT_ST);

	/* clear irq status */
	fsi_master_write(SOFT_RST, status);
	fsi_master_write(SOFT_RST, status | 0x00000010);

	if (int_st & INT_A_OUT)
		fsi_data_push(&master->fsia);
	if (int_st & INT_B_OUT)
		fsi_data_push(&master->fsib);

	fsi_master_write(INT_ST, 0x0000000);

	return IRQ_HANDLED;
}