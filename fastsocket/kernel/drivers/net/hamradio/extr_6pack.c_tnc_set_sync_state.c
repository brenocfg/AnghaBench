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
struct sixpack {int tnc_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tnc_set_sync_state (struct sixpack*,int) ; 

__attribute__((used)) static inline void tnc_set_sync_state(struct sixpack *sp, int new_tnc_state)
{
	int old_tnc_state = sp->tnc_state;

	if (old_tnc_state != new_tnc_state)
		__tnc_set_sync_state(sp, new_tnc_state);
}