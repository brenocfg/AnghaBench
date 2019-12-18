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
struct i2400m {int boot_mode; int rx_reorder; int /*<<< orphan*/  init_mutex; int /*<<< orphan*/  msg_completion; int /*<<< orphan*/  msg_mutex; void* rx_size_min; void* rx_pl_min; int /*<<< orphan*/  rx_lock; void* tx_size_min; void* tx_pl_min; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  state_wq; int /*<<< orphan*/  wimax_dev; } ;

/* Variables and functions */
 void* UINT_MAX ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wimax_dev_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline
void i2400m_init(struct i2400m *i2400m)
{
	wimax_dev_init(&i2400m->wimax_dev);

	i2400m->boot_mode = 1;
	i2400m->rx_reorder = 1;
	init_waitqueue_head(&i2400m->state_wq);

	spin_lock_init(&i2400m->tx_lock);
	i2400m->tx_pl_min = UINT_MAX;
	i2400m->tx_size_min = UINT_MAX;

	spin_lock_init(&i2400m->rx_lock);
	i2400m->rx_pl_min = UINT_MAX;
	i2400m->rx_size_min = UINT_MAX;

	mutex_init(&i2400m->msg_mutex);
	init_completion(&i2400m->msg_completion);

	mutex_init(&i2400m->init_mutex);
	/* wake_tx_ws is initialized in i2400m_tx_setup() */
}