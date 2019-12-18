#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
struct TYPE_8__ {int mask; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int mask; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int mask; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int mask; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_AND_STATUS_REG ; 
 int /*<<< orphan*/  CURRENT_SCSI_DATA_REG ; 
 int /*<<< orphan*/  INITIATOR_COMMAND_REG ; 
 int /*<<< orphan*/  MODE_REG ; 
 unsigned char NCR5380_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_REG ; 
 TYPE_4__* basrs ; 
 TYPE_3__* icrs ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_2__* mrs ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 TYPE_1__* signals ; 

__attribute__((used)) static void NCR5380_print(struct Scsi_Host *instance) {
    unsigned char status, data, basr, mr, icr, i;
    unsigned long flags;

    local_irq_save(flags);
    data = NCR5380_read(CURRENT_SCSI_DATA_REG);
    status = NCR5380_read(STATUS_REG);
    mr = NCR5380_read(MODE_REG);
    icr = NCR5380_read(INITIATOR_COMMAND_REG);
    basr = NCR5380_read(BUS_AND_STATUS_REG);
    local_irq_restore(flags);
    printk("STATUS_REG: %02x ", status);
    for (i = 0; signals[i].mask ; ++i) 
	if (status & signals[i].mask)
	    printk(",%s", signals[i].name);
    printk("\nBASR: %02x ", basr);
    for (i = 0; basrs[i].mask ; ++i) 
	if (basr & basrs[i].mask)
	    printk(",%s", basrs[i].name);
    printk("\nICR: %02x ", icr);
    for (i = 0; icrs[i].mask; ++i) 
	if (icr & icrs[i].mask)
	    printk(",%s", icrs[i].name);
    printk("\nMODE: %02x ", mr);
    for (i = 0; mrs[i].mask; ++i) 
	if (mr & mrs[i].mask)
	    printk(",%s", mrs[i].name);
    printk("\n");
}