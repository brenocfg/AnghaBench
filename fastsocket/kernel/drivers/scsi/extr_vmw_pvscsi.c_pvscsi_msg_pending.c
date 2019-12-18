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
struct pvscsi_adapter {struct PVSCSIRingsState* rings_state; } ;
struct PVSCSIRingsState {scalar_t__ msgProdIdx; scalar_t__ msgConsIdx; } ;

/* Variables and functions */

__attribute__((used)) static int pvscsi_msg_pending(const struct pvscsi_adapter *adapter)
{
	struct PVSCSIRingsState *s = adapter->rings_state;

	return s->msgProdIdx != s->msgConsIdx;
}