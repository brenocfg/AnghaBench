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
struct fc_seq {int dummy; } ;
struct fc_exch {void (* resp ) (struct fc_seq*,struct fc_frame*,void*) ;int /*<<< orphan*/  ex_lock; void* arg; } ;

/* Variables and functions */
 struct fc_exch* fc_seq_exch (struct fc_seq*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_seq_set_resp(struct fc_seq *sp,
			    void (*resp)(struct fc_seq *, struct fc_frame *,
					 void *),
			    void *arg)
{
	struct fc_exch *ep = fc_seq_exch(sp);

	spin_lock_bh(&ep->ex_lock);
	ep->resp = resp;
	ep->arg = arg;
	spin_unlock_bh(&ep->ex_lock);
}