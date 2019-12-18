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
typedef  int /*<<< orphan*/  u32 ;
struct wl1251 {int rx_current_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_REG_INTERRUPT_TRIG ; 
 int /*<<< orphan*/  ACX_REG_INTERRUPT_TRIG_H ; 
 int /*<<< orphan*/  INTR_TRIG_RX_PROC0 ; 
 int /*<<< orphan*/  INTR_TRIG_RX_PROC1 ; 
 int /*<<< orphan*/  wl1251_reg_write32 (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wl1251_rx_ack(struct wl1251 *wl)
{
	u32 data, addr;

	if (wl->rx_current_buffer) {
		addr = ACX_REG_INTERRUPT_TRIG_H;
		data = INTR_TRIG_RX_PROC1;
	} else {
		addr = ACX_REG_INTERRUPT_TRIG;
		data = INTR_TRIG_RX_PROC0;
	}

	wl1251_reg_write32(wl, addr, data);

	/* Toggle buffer ring */
	wl->rx_current_buffer = !wl->rx_current_buffer;
}