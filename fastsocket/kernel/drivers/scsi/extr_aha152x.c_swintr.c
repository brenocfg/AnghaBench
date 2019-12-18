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
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  swint; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMACNTRL0 ; 
 TYPE_1__* HOSTDATA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  INTEN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SETPORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t swintr(int irqno, void *dev_id)
{
	struct Scsi_Host *shpnt = dev_id;

	HOSTDATA(shpnt)->swint++;

	SETPORT(DMACNTRL0, INTEN);
	return IRQ_HANDLED;
}