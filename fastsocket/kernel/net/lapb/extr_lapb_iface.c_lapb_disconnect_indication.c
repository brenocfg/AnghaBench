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
struct TYPE_2__ {int /*<<< orphan*/  (* disconnect_indication ) (int /*<<< orphan*/ ,int) ;} ;
struct lapb_cb {int /*<<< orphan*/  dev; TYPE_1__ callbacks; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

void lapb_disconnect_indication(struct lapb_cb *lapb, int reason)
{
	if (lapb->callbacks.disconnect_indication)
		lapb->callbacks.disconnect_indication(lapb->dev, reason);
}