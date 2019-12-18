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
struct brcms_timer {struct brcms_timer* name; struct brcms_timer* next; } ;
struct TYPE_2__ {scalar_t__ fw_cnt; } ;
struct brcms_info {struct brcms_timer* timers; int /*<<< orphan*/  callbacks; int /*<<< orphan*/ * pub; int /*<<< orphan*/ * wlc; int /*<<< orphan*/  tasklet; scalar_t__ irq; int /*<<< orphan*/  ucode; TYPE_1__ fw; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcms_c_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcms_c_module_unregister (int /*<<< orphan*/ *,char*,struct brcms_info*) ; 
 int /*<<< orphan*/  brcms_debugfs_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcms_ucode_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct brcms_info*) ; 
 int /*<<< orphan*/  kfree (struct brcms_timer*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brcms_free(struct brcms_info *wl)
{
	struct brcms_timer *t, *next;

	/* free ucode data */
	if (wl->fw.fw_cnt)
		brcms_ucode_data_free(&wl->ucode);
	if (wl->irq)
		free_irq(wl->irq, wl);

	/* kill dpc */
	tasklet_kill(&wl->tasklet);

	if (wl->pub) {
		brcms_debugfs_detach(wl->pub);
		brcms_c_module_unregister(wl->pub, "linux", wl);
	}

	/* free common resources */
	if (wl->wlc) {
		brcms_c_detach(wl->wlc);
		wl->wlc = NULL;
		wl->pub = NULL;
	}

	/* virtual interface deletion is deferred so we cannot spinwait */

	/* wait for all pending callbacks to complete */
	while (atomic_read(&wl->callbacks) > 0)
		schedule();

	/* free timers */
	for (t = wl->timers; t; t = next) {
		next = t->next;
#ifdef DEBUG
		kfree(t->name);
#endif
		kfree(t);
	}
}