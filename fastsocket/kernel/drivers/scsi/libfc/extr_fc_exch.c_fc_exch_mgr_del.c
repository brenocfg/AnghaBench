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
struct fc_exch_mgr_anchor {TYPE_1__* mp; int /*<<< orphan*/  ema_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_exch_mgr_destroy ; 
 int /*<<< orphan*/  kfree (struct fc_exch_mgr_anchor*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void fc_exch_mgr_del(struct fc_exch_mgr_anchor *ema)
{
	/* remove EM anchor from EM anchors list */
	list_del(&ema->ema_list);
	kref_put(&ema->mp->kref, fc_exch_mgr_destroy);
	kfree(ema);
}