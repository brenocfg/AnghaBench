#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
struct TYPE_7__ {int mode; int /*<<< orphan*/  flags; TYPE_1__ DAPF; int /*<<< orphan*/  writeflush; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAP_BUFF_SIZE ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  F_WRITEFLUSH ; 
 int /*<<< orphan*/  F_WRITING ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 TYPE_3__ dev ; 
 int /*<<< orphan*/  get_play_delay_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interruptible_sleep_on_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_pending (TYPE_2__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dsp_write_flush(void)
{
	if (!(dev.mode & FMODE_WRITE) || !test_bit(F_WRITING, &dev.flags))
		return;
	set_bit(F_WRITEFLUSH, &dev.flags);
	interruptible_sleep_on_timeout(
		&dev.writeflush,
		get_play_delay_jiffies(dev.DAPF.len));
	clear_bit(F_WRITEFLUSH, &dev.flags);
	if (!signal_pending(current)) {
		current->state = TASK_INTERRUPTIBLE;
		schedule_timeout(get_play_delay_jiffies(DAP_BUFF_SIZE));
	}
	clear_bit(F_WRITING, &dev.flags);
}