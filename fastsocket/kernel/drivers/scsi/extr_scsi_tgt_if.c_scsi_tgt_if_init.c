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
 int misc_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_ring ; 
 int /*<<< orphan*/  tgt_miscdev ; 
 int /*<<< orphan*/  tgt_ring_exit (int /*<<< orphan*/ *) ; 
 int tgt_ring_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_ring ; 

int scsi_tgt_if_init(void)
{
	int err;

	err = tgt_ring_init(&tx_ring);
	if (err)
		return err;

	err = tgt_ring_init(&rx_ring);
	if (err)
		goto free_tx_ring;

	err = misc_register(&tgt_miscdev);
	if (err)
		goto free_rx_ring;

	return 0;
free_rx_ring:
	tgt_ring_exit(&rx_ring);
free_tx_ring:
	tgt_ring_exit(&tx_ring);

	return err;
}