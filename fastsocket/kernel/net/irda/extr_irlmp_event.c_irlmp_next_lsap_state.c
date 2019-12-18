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
struct lsap_cb {int /*<<< orphan*/  lsap_state; } ;
typedef  int /*<<< orphan*/  LSAP_STATE ;

/* Variables and functions */

__attribute__((used)) static inline void irlmp_next_lsap_state(struct lsap_cb *self,
					 LSAP_STATE state)
{
	/*
	IRDA_ASSERT(self != NULL, return;);
	IRDA_DEBUG(4, "%s(), LMP LSAP = %s\n", __func__, irlsap_state[state]);
	*/
	self->lsap_state = state;
}