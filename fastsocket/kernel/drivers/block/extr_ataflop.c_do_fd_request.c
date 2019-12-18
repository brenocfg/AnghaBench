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
struct request_queue {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  IRQ_MFP_FDC ; 
 int /*<<< orphan*/  atari_disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atari_enable_irq (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int fdc_busy ; 
 int /*<<< orphan*/  fdc_wait ; 
 int /*<<< orphan*/  floppy_irq ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_save_flags (unsigned long) ; 
 int /*<<< orphan*/  redo_fd_request () ; 
 int /*<<< orphan*/  sleep_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdma_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void do_fd_request(struct request_queue * q)
{
 	unsigned long flags;

	DPRINT(("do_fd_request for pid %d\n",current->pid));
	while( fdc_busy ) sleep_on( &fdc_wait );
	fdc_busy = 1;
	stdma_lock(floppy_irq, NULL);

	atari_disable_irq( IRQ_MFP_FDC );
	local_save_flags(flags);	/* The request function is called with ints
	local_irq_disable();		 * disabled... so must save the IPL for later */ 
	redo_fd_request();
	local_irq_restore(flags);
	atari_enable_irq( IRQ_MFP_FDC );
}