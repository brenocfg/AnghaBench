#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i2400m_roq_log {int dummy; } ;
struct i2400m {int rx_reorder; TYPE_1__* rx_roq; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct i2400m_roq_log* log; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2400M_RO_CIN ; 
 int /*<<< orphan*/  __i2400m_roq_init (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 scalar_t__ i2400m_rx_reorder_disabled ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 

int i2400m_rx_setup(struct i2400m *i2400m)
{
	int result = 0;
	struct device *dev = i2400m_dev(i2400m);

	i2400m->rx_reorder = i2400m_rx_reorder_disabled? 0 : 1;
	if (i2400m->rx_reorder) {
		unsigned itr;
		size_t size;
		struct i2400m_roq_log *rd;

		result = -ENOMEM;

		size = sizeof(i2400m->rx_roq[0]) * (I2400M_RO_CIN + 1);
		i2400m->rx_roq = kzalloc(size, GFP_KERNEL);
		if (i2400m->rx_roq == NULL) {
			dev_err(dev, "RX: cannot allocate %zu bytes for "
				"reorder queues\n", size);
			goto error_roq_alloc;
		}

		size = sizeof(*i2400m->rx_roq[0].log) * (I2400M_RO_CIN + 1);
		rd = kzalloc(size, GFP_KERNEL);
		if (rd == NULL) {
			dev_err(dev, "RX: cannot allocate %zu bytes for "
				"reorder queues log areas\n", size);
			result = -ENOMEM;
			goto error_roq_log_alloc;
		}

		for(itr = 0; itr < I2400M_RO_CIN + 1; itr++) {
			__i2400m_roq_init(&i2400m->rx_roq[itr]);
			i2400m->rx_roq[itr].log = &rd[itr];
		}
	}
	return 0;

error_roq_log_alloc:
	kfree(i2400m->rx_roq);
error_roq_alloc:
	return result;
}