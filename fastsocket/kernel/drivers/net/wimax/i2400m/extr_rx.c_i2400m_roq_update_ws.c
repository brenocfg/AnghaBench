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
struct i2400m_roq {unsigned int ws; int /*<<< orphan*/  queue; } ;
struct i2400m {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2400M_RO_TYPE_WS ; 
 unsigned int __i2400m_roq_update_ws (struct i2400m*,struct i2400m_roq*,unsigned int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*,struct i2400m_roq*,unsigned int) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int /*<<< orphan*/  i2400m_roq_log_add (struct i2400m*,struct i2400m_roq*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 unsigned int skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void i2400m_roq_update_ws(struct i2400m *i2400m, struct i2400m_roq *roq,
			  unsigned sn)
{
	struct device *dev = i2400m_dev(i2400m);
	unsigned old_ws, nsn, len;

	d_fnstart(2, dev, "(i2400m %p roq %p sn %u)\n", i2400m, roq, sn);
	old_ws = roq->ws;
	len = skb_queue_len(&roq->queue);
	nsn = __i2400m_roq_update_ws(i2400m, roq, sn);
	i2400m_roq_log_add(i2400m, roq, I2400M_RO_TYPE_WS,
			     old_ws, len, sn, nsn, roq->ws);
	d_fnstart(2, dev, "(i2400m %p roq %p sn %u) = void\n", i2400m, roq, sn);
	return;
}