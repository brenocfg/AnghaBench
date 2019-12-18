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
struct et131x_adapter {scalar_t__ duplex_mode; scalar_t__ FlowControl; scalar_t__ RegistryFlowControl; } ;

/* Variables and functions */
 scalar_t__ Both ; 
 int /*<<< orphan*/  ET1310_PhyAccessMiBit (struct et131x_adapter*,int /*<<< orphan*/ ,int,int,char*) ; 
 void* None ; 
 scalar_t__ RxOnly ; 
 char TRUEPHY_BIT_CLEAR ; 
 int /*<<< orphan*/  TRUEPHY_BIT_READ ; 
 char TRUEPHY_BIT_SET ; 

void ConfigFlowControl(struct et131x_adapter *etdev)
{
	if (etdev->duplex_mode == 0) {
		etdev->FlowControl = None;
	} else {
		char RemotePause, RemoteAsyncPause;

		ET1310_PhyAccessMiBit(etdev,
				      TRUEPHY_BIT_READ, 5, 10, &RemotePause);
		ET1310_PhyAccessMiBit(etdev,
				      TRUEPHY_BIT_READ, 5, 11,
				      &RemoteAsyncPause);

		if ((RemotePause == TRUEPHY_BIT_SET) &&
		    (RemoteAsyncPause == TRUEPHY_BIT_SET)) {
			etdev->FlowControl = etdev->RegistryFlowControl;
		} else if ((RemotePause == TRUEPHY_BIT_SET) &&
			   (RemoteAsyncPause == TRUEPHY_BIT_CLEAR)) {
			if (etdev->RegistryFlowControl == Both)
				etdev->FlowControl = Both;
			else
				etdev->FlowControl = None;
		} else if ((RemotePause == TRUEPHY_BIT_CLEAR) &&
			   (RemoteAsyncPause == TRUEPHY_BIT_CLEAR)) {
			etdev->FlowControl = None;
		} else {/* if (RemotePause == TRUEPHY_CLEAR_BIT &&
			       RemoteAsyncPause == TRUEPHY_SET_BIT) */
			if (etdev->RegistryFlowControl == Both)
				etdev->FlowControl = RxOnly;
			else
				etdev->FlowControl = None;
		}
	}
}