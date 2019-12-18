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
struct Scsi_Host {int this_id; int cmd_per_lun; int can_queue; scalar_t__ hostt; } ;
struct TYPE_2__ {int id_mask; int id_higher_mask; int /*<<< orphan*/  flags; int /*<<< orphan*/ * disconnected_queue; int /*<<< orphan*/ * issue_queue; int /*<<< orphan*/ * connected; scalar_t__ targets_present; scalar_t__ dma_len; scalar_t__* busy; scalar_t__ aborted; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_CHECK_LAST_BYTE_SENT ; 
 int /*<<< orphan*/  HOSTNO ; 
 int /*<<< orphan*/  ICR_BASE ; 
 int /*<<< orphan*/  INITIATOR_COMMAND_REG ; 
 int /*<<< orphan*/  MODE_REG ; 
 int /*<<< orphan*/  MR_BASE ; 
 int /*<<< orphan*/  NCR5380_all_init () ; 
 int /*<<< orphan*/  NCR5380_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SELECT_ENABLE_REG ; 
 int /*<<< orphan*/  SETUP_HOSTDATA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  TARGET_COMMAND_REG ; 
 struct Scsi_Host* first_instance ; 
 TYPE_1__* hostdata ; 
 int /*<<< orphan*/  init_tags () ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ the_template ; 

__attribute__((used)) static int NCR5380_init (struct Scsi_Host *instance, int flags)
{
    int i;
    SETUP_HOSTDATA(instance);

    NCR5380_all_init();

    hostdata->aborted = 0;
    hostdata->id_mask = 1 << instance->this_id;
    hostdata->id_higher_mask = 0;
    for (i = hostdata->id_mask; i <= 0x80; i <<= 1)
	if (i > hostdata->id_mask)
	    hostdata->id_higher_mask |= i;
    for (i = 0; i < 8; ++i)
	hostdata->busy[i] = 0;
#ifdef SUPPORT_TAGS
    init_tags();
#endif
#if defined (REAL_DMA)
    hostdata->dma_len = 0;
#endif
    hostdata->targets_present = 0;
    hostdata->connected = NULL;
    hostdata->issue_queue = NULL;
    hostdata->disconnected_queue = NULL;
    hostdata->flags = FLAG_CHECK_LAST_BYTE_SENT;

    if (!the_template) {
	the_template = instance->hostt;
	first_instance = instance;
    }
	

#ifndef AUTOSENSE
    if ((instance->cmd_per_lun > 1) || (instance->can_queue > 1))
	 printk("scsi%d: WARNING : support for multiple outstanding commands enabled\n"
	        "        without AUTOSENSE option, contingent allegiance conditions may\n"
	        "        be incorrectly cleared.\n", HOSTNO);
#endif /* def AUTOSENSE */

    NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE);
    NCR5380_write(MODE_REG, MR_BASE);
    NCR5380_write(TARGET_COMMAND_REG, 0);
    NCR5380_write(SELECT_ENABLE_REG, 0);

    return 0;
}