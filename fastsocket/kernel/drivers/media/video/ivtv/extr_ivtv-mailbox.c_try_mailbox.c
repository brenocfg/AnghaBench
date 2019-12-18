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
typedef  int u32 ;
struct ivtv_mailbox_data {TYPE_1__* mbox; int /*<<< orphan*/  busy; } ;
struct ivtv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_MBOX_DRIVER_BUSY ; 
 int IVTV_MBOX_FIRMWARE_DONE ; 
 int IVTV_MBOX_FREE ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int try_mailbox(struct ivtv *itv, struct ivtv_mailbox_data *mbdata, int mb)
{
	u32 flags = readl(&mbdata->mbox[mb].flags);
	int is_free = flags == IVTV_MBOX_FREE || (flags & IVTV_MBOX_FIRMWARE_DONE);

	/* if the mailbox is free, then try to claim it */
	if (is_free && !test_and_set_bit(mb, &mbdata->busy)) {
		write_sync(IVTV_MBOX_DRIVER_BUSY, &mbdata->mbox[mb].flags);
		return 1;
	}
	return 0;
}