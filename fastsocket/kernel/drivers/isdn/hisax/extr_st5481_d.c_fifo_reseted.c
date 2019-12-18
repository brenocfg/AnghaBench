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
struct TYPE_2__ {int /*<<< orphan*/  fsm; } ;
struct st5481_adapter {TYPE_1__ d_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_DOUT_RESETED ; 
 int /*<<< orphan*/  FsmEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fifo_reseted(void *context)
{
	struct st5481_adapter *adapter = context;

	FsmEvent(&adapter->d_out.fsm, EV_DOUT_RESETED, NULL);
}