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
typedef  int /*<<< orphan*/  u32 ;
struct dccp_sock {struct ccid* dccps_hc_tx_ccid; } ;
struct ccid {TYPE_1__* ccid_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  ccid_ccmps; } ;

/* Variables and functions */

__attribute__((used)) static u32 dccp_determine_ccmps(const struct dccp_sock *dp)
{
	const struct ccid *tx_ccid = dp->dccps_hc_tx_ccid;

	if (tx_ccid == NULL || tx_ccid->ccid_ops == NULL)
		return 0;
	return tx_ccid->ccid_ops->ccid_ccmps;
}