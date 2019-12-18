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
struct TYPE_2__ {int reset; } ;

/* Variables and functions */
 TYPE_1__* FDCS ; 
 int FD_RESET_ALWAYS ; 
 int /*<<< orphan*/  LOCK_FDC (int,int) ; 
 int /*<<< orphan*/  WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cont ; 
 int /*<<< orphan*/  process_fd_request () ; 
 int /*<<< orphan*/  reset_cont ; 
 int /*<<< orphan*/  reset_fdc ; 

__attribute__((used)) static int user_reset_fdc(int drive, int arg, int interruptible)
{
	int ret;

	ret = 0;
	LOCK_FDC(drive, interruptible);
	if (arg == FD_RESET_ALWAYS)
		FDCS->reset = 1;
	if (FDCS->reset) {
		cont = &reset_cont;
		WAIT(reset_fdc);
	}
	process_fd_request();
	return ret;
}