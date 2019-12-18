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
typedef  int /*<<< orphan*/  u8 ;
struct ks8851_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ks_dbg (struct ks8851_net*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ks8851_dbg_dumpkkt(struct ks8851_net *ks, u8 *rxpkt)
{
	ks_dbg(ks, "pkt %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x\n",
	       rxpkt[4], rxpkt[5], rxpkt[6], rxpkt[7],
	       rxpkt[8], rxpkt[9], rxpkt[10], rxpkt[11],
	       rxpkt[12], rxpkt[13], rxpkt[14], rxpkt[15]);
}