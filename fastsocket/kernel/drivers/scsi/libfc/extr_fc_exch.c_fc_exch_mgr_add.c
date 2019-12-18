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
struct fc_lport {int /*<<< orphan*/  ema_list; } ;
struct fc_exch_mgr_anchor {int (* match ) (struct fc_frame*) ;int /*<<< orphan*/  ema_list; struct fc_exch_mgr* mp; } ;
struct fc_exch_mgr {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct fc_exch_mgr_anchor* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct fc_exch_mgr_anchor *fc_exch_mgr_add(struct fc_lport *lport,
					   struct fc_exch_mgr *mp,
					   bool (*match)(struct fc_frame *))
{
	struct fc_exch_mgr_anchor *ema;

	ema = kmalloc(sizeof(*ema), GFP_ATOMIC);
	if (!ema)
		return ema;

	ema->mp = mp;
	ema->match = match;
	/* add EM anchor to EM anchors list */
	list_add_tail(&ema->ema_list, &lport->ema_list);
	kref_get(&mp->kref);
	return ema;
}