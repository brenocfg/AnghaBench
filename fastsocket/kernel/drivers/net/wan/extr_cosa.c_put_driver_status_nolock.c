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
struct cosa_data {int rxbitmap; int txbitmap; int enabled; } ;

/* Variables and functions */
 int DRIVER_RX_READY ; 
 int DRIVER_TXMAP_MASK ; 
 int DRIVER_TXMAP_SHIFT ; 
 int DRIVER_TX_READY ; 
 int /*<<< orphan*/  SR_RX_INT_ENA ; 
 int /*<<< orphan*/  cosa_putdata8 (struct cosa_data*,int) ; 
 int /*<<< orphan*/  cosa_putstatus (struct cosa_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_data_cmd (struct cosa_data*,int) ; 
 int /*<<< orphan*/  debug_status_out (struct cosa_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_driver_status_nolock(struct cosa_data *cosa)
{
	int status;

	status = (cosa->rxbitmap ? DRIVER_RX_READY : 0)
		| (cosa->txbitmap ? DRIVER_TX_READY : 0)
		| (cosa->txbitmap? ~(cosa->txbitmap<<DRIVER_TXMAP_SHIFT)
			&DRIVER_TXMAP_MASK : 0);

	if (cosa->rxbitmap|cosa->txbitmap) {
		cosa_putstatus(cosa, SR_RX_INT_ENA);
#ifdef DEBUG_IO
		debug_status_out(cosa, SR_RX_INT_ENA);
#endif
		cosa->enabled = 1;
	} else {
		cosa_putstatus(cosa, 0);
#ifdef DEBUG_IO
		debug_status_out(cosa, 0);
#endif
		cosa->enabled = 0;
	}
	cosa_putdata8(cosa, status);
#ifdef DEBUG_IO
	debug_data_cmd(cosa, status);
#endif
}