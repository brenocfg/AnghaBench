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
struct TYPE_2__ {int /*<<< orphan*/  serio; } ;
struct atkbd {TYPE_1__ ps2dev; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  serio_continue_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_pause_rx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void atkbd_disable(struct atkbd *atkbd)
{
	serio_pause_rx(atkbd->ps2dev.serio);
	atkbd->enabled = 0;
	serio_continue_rx(atkbd->ps2dev.serio);
}