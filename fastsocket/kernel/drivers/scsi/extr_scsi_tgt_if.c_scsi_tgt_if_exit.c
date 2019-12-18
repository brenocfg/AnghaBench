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

/* Variables and functions */
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_ring ; 
 int /*<<< orphan*/  tgt_miscdev ; 
 int /*<<< orphan*/  tgt_ring_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_ring ; 

void scsi_tgt_if_exit(void)
{
	tgt_ring_exit(&tx_ring);
	tgt_ring_exit(&rx_ring);
	misc_deregister(&tgt_miscdev);
}