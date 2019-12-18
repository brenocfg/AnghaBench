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
struct TYPE_2__ {int mode; int /*<<< orphan*/  DARF; int /*<<< orphan*/  DAPF; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 TYPE_1__ dev ; 
 int /*<<< orphan*/  msnd_fifo_make_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_play_queue () ; 
 int /*<<< orphan*/  reset_record_queue () ; 

__attribute__((used)) static void reset_queues(void)
{
	if (dev.mode & FMODE_WRITE) {
		msnd_fifo_make_empty(&dev.DAPF);
		reset_play_queue();
	}
	if (dev.mode & FMODE_READ) {
		msnd_fifo_make_empty(&dev.DARF);
		reset_record_queue();
	}
}