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
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_dropped; } ;
struct vport {int /*<<< orphan*/  stats_lock; TYPE_1__ err_stats; } ;
typedef  enum vport_err_type { ____Placeholder_vport_err_type } vport_err_type ;

/* Variables and functions */
#define  VPORT_E_RX_DROPPED 131 
#define  VPORT_E_RX_ERROR 130 
#define  VPORT_E_TX_DROPPED 129 
#define  VPORT_E_TX_ERROR 128 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ovs_vport_record_error(struct vport *vport, enum vport_err_type err_type)
{
	spin_lock(&vport->stats_lock);

	switch (err_type) {
	case VPORT_E_RX_DROPPED:
		vport->err_stats.rx_dropped++;
		break;

	case VPORT_E_RX_ERROR:
		vport->err_stats.rx_errors++;
		break;

	case VPORT_E_TX_DROPPED:
		vport->err_stats.tx_dropped++;
		break;

	case VPORT_E_TX_ERROR:
		vport->err_stats.tx_errors++;
		break;
	}

	spin_unlock(&vport->stats_lock);
}