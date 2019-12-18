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
struct bfa_trc_mod_s {int /*<<< orphan*/  ntrc; scalar_t__ stopped; scalar_t__ tail; scalar_t__ head; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_TRC_MAX ; 

__attribute__((used)) static inline void
bfa_trc_init(struct bfa_trc_mod_s *trcm)
{
	trcm->head = trcm->tail = trcm->stopped = 0;
	trcm->ntrc = BFA_TRC_MAX;
}