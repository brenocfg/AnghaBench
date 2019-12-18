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
struct rtl8169_private {scalar_t__ RxDescArray; void** Rx_databuff; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int NUM_RX_DESC ; 
 void* rtl8169_alloc_rx_data (struct rtl8169_private*,scalar_t__) ; 
 int /*<<< orphan*/  rtl8169_make_unusable_by_asic (scalar_t__) ; 
 int /*<<< orphan*/  rtl8169_mark_as_last_descriptor (scalar_t__) ; 
 int /*<<< orphan*/  rtl8169_rx_clear (struct rtl8169_private*) ; 

__attribute__((used)) static int rtl8169_rx_fill(struct rtl8169_private *tp)
{
	unsigned int i;

	for (i = 0; i < NUM_RX_DESC; i++) {
		void *data;

		if (tp->Rx_databuff[i])
			continue;

		data = rtl8169_alloc_rx_data(tp, tp->RxDescArray + i);
		if (!data) {
			rtl8169_make_unusable_by_asic(tp->RxDescArray + i);
			goto err_out;
		}
		tp->Rx_databuff[i] = data;
	}

	rtl8169_mark_as_last_descriptor(tp->RxDescArray + NUM_RX_DESC - 1);
	return 0;

err_out:
	rtl8169_rx_clear(tp);
	return -ENOMEM;
}