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
struct br2684_vcc {TYPE_1__* atmvcc; int /*<<< orphan*/  (* old_push ) (TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  brvccs; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/ * user_back; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  devs_lock ; 
 int /*<<< orphan*/  kfree (struct br2684_vcc*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct br2684_vcc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br2684_close_vcc(struct br2684_vcc *brvcc)
{
	pr_debug("removing VCC %p from dev %p\n", brvcc, brvcc->device);
	write_lock_irq(&devs_lock);
	list_del(&brvcc->brvccs);
	write_unlock_irq(&devs_lock);
	brvcc->atmvcc->user_back = NULL;	/* what about vcc->recvq ??? */
	brvcc->old_push(brvcc->atmvcc, NULL);	/* pass on the bad news */
	kfree(brvcc);
	module_put(THIS_MODULE);
}