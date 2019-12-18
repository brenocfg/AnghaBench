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
typedef  int /*<<< orphan*/  isdn_net_local ;

/* Variables and functions */
 int /*<<< orphan*/  isdn_net_rm_from_bundle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isdn_net_lp_disconnected(isdn_net_local *lp)
{
	isdn_net_rm_from_bundle(lp);
}