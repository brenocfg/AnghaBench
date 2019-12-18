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
struct emac_instance {size_t rx_slot; TYPE_1__* rx_desc; } ;
struct TYPE_2__ {int ctrl; } ;

/* Variables and functions */
 int MAL_RX_CTRL_EMPTY ; 

__attribute__((used)) static int emac_peek_rx(void *param)
{
	struct emac_instance *dev = param;

	return !(dev->rx_desc[dev->rx_slot].ctrl & MAL_RX_CTRL_EMPTY);
}