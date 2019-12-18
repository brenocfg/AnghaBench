#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tg3 {int /*<<< orphan*/  reset_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESET_TASK_PENDING ; 
 int /*<<< orphan*/  TX_RECOVERY_PENDING ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tg3_flag_clear (struct tg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tg3_reset_task_cancel(struct tg3 *tp)
{
	cancel_work_sync(&tp->reset_task);
	tg3_flag_clear(tp, RESET_TASK_PENDING);
	tg3_flag_clear(tp, TX_RECOVERY_PENDING);
}