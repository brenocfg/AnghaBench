#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wlandevice_t ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ hfa384x_usbin_t ;

/* Variables and functions */
 scalar_t__ HFA384x_TXSTATUS_ISERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prism2sta_ev_tx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prism2sta_ev_txexc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hfa384x_usbin_txcompl(wlandevice_t *wlandev,
				  hfa384x_usbin_t *usbin)
{
	u16 status;

	status = le16_to_cpu(usbin->type);	/* yeah I know it says type... */

	/* Was there an error? */
	if (HFA384x_TXSTATUS_ISERROR(status))
		prism2sta_ev_txexc(wlandev, status);
	else
		prism2sta_ev_tx(wlandev, status);
}