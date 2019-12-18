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
struct wl1251 {int data_in_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_REG_INTERRUPT_TRIG ; 
 int /*<<< orphan*/  ACX_REG_INTERRUPT_TRIG_H ; 
 int /*<<< orphan*/  INTR_TRIG_TX_PROC0 ; 
 int /*<<< orphan*/  INTR_TRIG_TX_PROC1 ; 
 int TX_STATUS_DATA_OUT_COUNT_MASK ; 
 int /*<<< orphan*/  wl1251_reg_write32 (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wl1251_tx_trigger(struct wl1251 *wl)
{
	u32 data, addr;

	if (wl->data_in_count & 0x1) {
		addr = ACX_REG_INTERRUPT_TRIG_H;
		data = INTR_TRIG_TX_PROC1;
	} else {
		addr = ACX_REG_INTERRUPT_TRIG;
		data = INTR_TRIG_TX_PROC0;
	}

	wl1251_reg_write32(wl, addr, data);

	/* Bumping data in */
	wl->data_in_count = (wl->data_in_count + 1) &
		TX_STATUS_DATA_OUT_COUNT_MASK;
}