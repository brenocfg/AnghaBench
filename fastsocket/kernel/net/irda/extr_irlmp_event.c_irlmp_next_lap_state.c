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
struct lap_cb {int /*<<< orphan*/  lap_state; } ;
typedef  int /*<<< orphan*/  IRLMP_STATE ;

/* Variables and functions */

__attribute__((used)) static inline void irlmp_next_lap_state(struct lap_cb *self,
					IRLMP_STATE state)
{
	/*
	IRDA_DEBUG(4, "%s(), LMP LAP = %s\n", __func__, irlmp_state[state]);
	*/
	self->lap_state = state;
}