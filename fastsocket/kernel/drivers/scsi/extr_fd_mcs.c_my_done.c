#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
struct TYPE_3__ {int result; int /*<<< orphan*/  (* scsi_done ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Interrupt_Cntl_port ; 
 TYPE_1__* current_SC ; 
 int /*<<< orphan*/  fd_mcs_make_bus_idle (struct Scsi_Host*) ; 
 scalar_t__ in_command ; 
 scalar_t__ in_interrupt_flag ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void my_done(struct Scsi_Host *shpnt, int error)
{
	if (in_command) {
		in_command = 0;
		outb(0x00, Interrupt_Cntl_port);
		fd_mcs_make_bus_idle(shpnt);
		current_SC->result = error;
		current_SC->scsi_done(current_SC);
	} else {
		panic("fd_mcs: my_done() called outside of command\n");
	}
#if DEBUG_RACE
	in_interrupt_flag = 0;
#endif
}