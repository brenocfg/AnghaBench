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
typedef  int /*<<< orphan*/  timeout_fn ;
struct TYPE_4__ {int dtr; } ;
struct TYPE_3__ {int rate; } ;

/* Variables and functions */
 TYPE_2__* FDCS ; 
 int /*<<< orphan*/  FD_DCR ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  fd_outb (int,int /*<<< orphan*/ ) ; 
 int fd_wait_for_completion (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ floppy_ready ; 
 scalar_t__ jiffies ; 
 TYPE_1__* raw_cmd ; 

__attribute__((used)) static int fdc_dtr(void)
{
	/* If data rate not already set to desired value, set it. */
	if ((raw_cmd->rate & 3) == FDCS->dtr)
		return 0;

	/* Set dtr */
	fd_outb(raw_cmd->rate & 3, FD_DCR);

	/* TODO: some FDC/drive combinations (C&T 82C711 with TEAC 1.2MB)
	 * need a stabilization period of several milliseconds to be
	 * enforced after data rate changes before R/W operations.
	 * Pause 5 msec to avoid trouble. (Needs to be 2 jiffies)
	 */
	FDCS->dtr = raw_cmd->rate & 3;
	return (fd_wait_for_completion(jiffies + 2UL * HZ / 100,
				       (timeout_fn) floppy_ready));
}