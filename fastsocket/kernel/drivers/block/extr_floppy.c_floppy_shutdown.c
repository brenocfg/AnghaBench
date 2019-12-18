#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int reset; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* redo ) () ;int /*<<< orphan*/  (* done ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 TYPE_2__* FDCS ; 
 int /*<<< orphan*/  cancel_activity () ; 
 unsigned long claim_dma_lock () ; 
 TYPE_1__* cont ; 
 int /*<<< orphan*/  fd_disable_dma () ; 
 int /*<<< orphan*/  floppy_enable_hlt () ; 
 int /*<<< orphan*/  initialising ; 
 int /*<<< orphan*/  is_alive (char*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  process_fd_request () ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  show_floppy () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static void floppy_shutdown(unsigned long data)
{
	unsigned long flags;

	if (!initialising)
		show_floppy();
	cancel_activity();

	floppy_enable_hlt();

	flags = claim_dma_lock();
	fd_disable_dma();
	release_dma_lock(flags);

	/* avoid dma going to a random drive after shutdown */

	if (!initialising)
		DPRINT("floppy timeout called\n");
	FDCS->reset = 1;
	if (cont) {
		cont->done(0);
		cont->redo();	/* this will recall reset when needed */
	} else {
		printk("no cont in shutdown!\n");
		process_fd_request();
	}
	is_alive("floppy shutdown");
}