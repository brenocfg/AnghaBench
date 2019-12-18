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
struct sk_buff {int /*<<< orphan*/  cb; } ;
struct i2400m_roq_data {int /*<<< orphan*/  cs; } ;
struct i2400m_roq {unsigned int ws; int /*<<< orphan*/  queue; } ;
struct i2400m {int /*<<< orphan*/  (* bus_reset ) (struct i2400m*,int /*<<< orphan*/ ) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2400M_RO_TYPE_PACKET_WS ; 
 int /*<<< orphan*/  I2400M_RT_WARM ; 
 unsigned int __i2400m_roq_nsn (struct i2400m_roq*,unsigned int) ; 
 int /*<<< orphan*/  __i2400m_roq_queue (struct i2400m*,struct i2400m_roq*,struct sk_buff*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  __i2400m_roq_update_ws (struct i2400m*,struct i2400m_roq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400m*,struct i2400m_roq*,struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*,struct i2400m_roq*,struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int,unsigned int,unsigned int) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int /*<<< orphan*/  i2400m_net_erx (struct i2400m*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2400m_roq_log_add (struct i2400m*,struct i2400m_roq*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  i2400m_roq_log_dump (struct i2400m*,struct i2400m_roq*) ; 
 unsigned int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct i2400m*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static
void i2400m_roq_queue_update_ws(struct i2400m *i2400m, struct i2400m_roq *roq,
				struct sk_buff * skb, unsigned sn)
{
	struct device *dev = i2400m_dev(i2400m);
	unsigned nsn, old_ws, len;

	d_fnstart(2, dev, "(i2400m %p roq %p skb %p sn %u)\n",
		  i2400m, roq, skb, sn);
	len = skb_queue_len(&roq->queue);
	nsn = __i2400m_roq_nsn(roq, sn);
	old_ws = roq->ws;
	if (unlikely(nsn >= 1024)) {
		dev_err(dev, "SW BUG? queue_update_ws nsn %u (sn %u ws %u)\n",
			nsn, sn, roq->ws);
		i2400m_roq_log_dump(i2400m, roq);
		i2400m->bus_reset(i2400m, I2400M_RT_WARM);
	} else {
		/* if the queue is empty, don't bother as we'd queue
		 * it and inmediately unqueue it -- just deliver it */
		if (len == 0) {
			struct i2400m_roq_data *roq_data;
			roq_data = (struct i2400m_roq_data *) &skb->cb;
			i2400m_net_erx(i2400m, skb, roq_data->cs);
		}
		else
			__i2400m_roq_queue(i2400m, roq, skb, sn, nsn);
		__i2400m_roq_update_ws(i2400m, roq, sn + 1);
		i2400m_roq_log_add(i2400m, roq, I2400M_RO_TYPE_PACKET_WS,
				   old_ws, len, sn, nsn, roq->ws);
	}
	d_fnend(2, dev, "(i2400m %p roq %p skb %p sn %u) = void\n",
		i2400m, roq, skb, sn);
	return;
}