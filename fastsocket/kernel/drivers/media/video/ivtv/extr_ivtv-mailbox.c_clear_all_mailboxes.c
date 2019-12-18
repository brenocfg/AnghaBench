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
struct ivtv_mailbox_data {int max_mbox; int /*<<< orphan*/  busy; TYPE_1__* mbox; } ;
struct ivtv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_WARN (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_all_mailboxes(struct ivtv *itv, struct ivtv_mailbox_data *mbdata)
{
	int i;

	for (i = 0; i <= mbdata->max_mbox; i++) {
		IVTV_DEBUG_WARN("Clearing mailbox %d: cmd 0x%08x flags 0x%08x\n",
			i, readl(&mbdata->mbox[i].cmd), readl(&mbdata->mbox[i].flags));
		write_sync(0, &mbdata->mbox[i].flags);
		clear_bit(i, &mbdata->busy);
	}
}