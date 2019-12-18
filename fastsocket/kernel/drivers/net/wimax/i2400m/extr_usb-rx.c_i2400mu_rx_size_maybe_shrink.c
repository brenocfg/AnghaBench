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
struct i2400mu {int rx_size_cnt; size_t rx_size_acc; int rx_size; scalar_t__ rx_size_auto_shrink; TYPE_1__* usb_iface; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_printf (int,struct device*,char*,size_t,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static
void i2400mu_rx_size_maybe_shrink(struct i2400mu *i2400mu)
{
	const size_t max_pkt_size = 512;
	struct device *dev = &i2400mu->usb_iface->dev;

	if (unlikely(i2400mu->rx_size_cnt >= 100
		     && i2400mu->rx_size_auto_shrink)) {
		size_t avg_rx_size =
			i2400mu->rx_size_acc / i2400mu->rx_size_cnt;
		size_t new_rx_size = i2400mu->rx_size / 2;
		if (avg_rx_size < new_rx_size) {
			if (new_rx_size % max_pkt_size == 0) {
				new_rx_size -= 8;
				d_printf(1, dev,
					 "RX: expected size shrank to %zu "
					 "[adjusted -8] from %zu\n",
					 new_rx_size, i2400mu->rx_size);
			} else
				d_printf(1, dev,
					 "RX: expected size shrank to %zu "
					 "from %zu\n",
					 new_rx_size, i2400mu->rx_size);
			i2400mu->rx_size = new_rx_size;
			i2400mu->rx_size_cnt = 0;
			i2400mu->rx_size_acc = i2400mu->rx_size;
		}
	}
}