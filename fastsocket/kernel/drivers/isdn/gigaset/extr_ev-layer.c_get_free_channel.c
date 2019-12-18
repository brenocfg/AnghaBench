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
struct cardstate {int channels; int /*<<< orphan*/  lock; int /*<<< orphan*/  temp_at_states; TYPE_1__* bcs; } ;
struct at_state_t {int cid; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {struct at_state_t at_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  gigaset_at_init (struct at_state_t*,int /*<<< orphan*/ *,struct cardstate*,int) ; 
 scalar_t__ gigaset_get_channel (TYPE_1__*) ; 
 struct at_state_t* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline struct at_state_t *get_free_channel(struct cardstate *cs,
						  int cid)
/* cids: >0: siemens-cid
	  0: without cid
	 -1: no cid assigned yet
*/
{
	unsigned long flags;
	int i;
	struct at_state_t *ret;

	for (i = 0; i < cs->channels; ++i)
		if (gigaset_get_channel(cs->bcs + i)) {
			ret = &cs->bcs[i].at_state;
			ret->cid = cid;
			return ret;
		}

	spin_lock_irqsave(&cs->lock, flags);
	ret = kmalloc(sizeof(struct at_state_t), GFP_ATOMIC);
	if (ret) {
		gigaset_at_init(ret, NULL, cs, cid);
		list_add(&ret->list, &cs->temp_at_states);
	}
	spin_unlock_irqrestore(&cs->lock, flags);
	return ret;
}