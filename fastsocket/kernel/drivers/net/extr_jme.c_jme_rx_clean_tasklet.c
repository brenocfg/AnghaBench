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
struct dynpcc_info {int /*<<< orphan*/  intr_cnt; } ;
struct jme_adapter {int /*<<< orphan*/  rx_ring_size; struct dynpcc_info dpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  jme_process_receive (struct jme_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
jme_rx_clean_tasklet(unsigned long arg)
{
	struct jme_adapter *jme = (struct jme_adapter *)arg;
	struct dynpcc_info *dpi = &(jme->dpi);

	jme_process_receive(jme, jme->rx_ring_size);
	++(dpi->intr_cnt);

}