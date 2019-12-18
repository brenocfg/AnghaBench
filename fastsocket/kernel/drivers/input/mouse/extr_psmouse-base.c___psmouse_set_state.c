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
struct TYPE_2__ {scalar_t__ flags; } ;
struct psmouse {int state; int /*<<< orphan*/  last; TYPE_1__ ps2dev; scalar_t__ out_of_sync_cnt; scalar_t__ pktcnt; } ;
typedef  enum psmouse_state { ____Placeholder_psmouse_state } psmouse_state ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static inline void __psmouse_set_state(struct psmouse *psmouse, enum psmouse_state new_state)
{
	psmouse->state = new_state;
	psmouse->pktcnt = psmouse->out_of_sync_cnt = 0;
	psmouse->ps2dev.flags = 0;
	psmouse->last = jiffies;
}