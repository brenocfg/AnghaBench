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
struct bigmac {int /*<<< orphan*/  bregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  bigmac_rx_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bigmac_tx_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bigmac_stop(struct bigmac *bp)
{
	bigmac_tx_reset(bp->bregs);
	bigmac_rx_reset(bp->bregs);
}