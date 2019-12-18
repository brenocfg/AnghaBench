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
struct i2400m_roq_log_entry {int type; unsigned int ws; unsigned int count; unsigned int sn; unsigned int nsn; unsigned int new_ws; } ;
struct i2400m_roq {TYPE_1__* log; } ;
struct i2400m {int dummy; } ;
typedef  enum i2400m_ro_type { ____Placeholder_i2400m_ro_type } i2400m_ro_type ;
struct TYPE_2__ {unsigned int in; unsigned int out; struct i2400m_roq_log_entry* entry; } ;

/* Variables and functions */
 unsigned int I2400M_ROQ_LOG_LENGTH ; 
 int __i2400m_roq_index (struct i2400m*,struct i2400m_roq*) ; 
 scalar_t__ d_test (int) ; 
 int /*<<< orphan*/  i2400m_roq_log_entry_print (struct i2400m*,int,unsigned int,struct i2400m_roq_log_entry*) ; 

__attribute__((used)) static
void i2400m_roq_log_add(struct i2400m *i2400m,
			struct i2400m_roq *roq, enum i2400m_ro_type type,
			unsigned ws, unsigned count, unsigned sn,
			unsigned nsn, unsigned new_ws)
{
	struct i2400m_roq_log_entry *e;
	unsigned cnt_idx;
	int index = __i2400m_roq_index(i2400m, roq);

	/* if we run out of space, we eat from the end */
	if (roq->log->in - roq->log->out == I2400M_ROQ_LOG_LENGTH)
		roq->log->out++;
	cnt_idx = roq->log->in++ % I2400M_ROQ_LOG_LENGTH;
	e = &roq->log->entry[cnt_idx];

	e->type = type;
	e->ws = ws;
	e->count = count;
	e->sn = sn;
	e->nsn = nsn;
	e->new_ws = new_ws;

	if (d_test(1))
		i2400m_roq_log_entry_print(i2400m, index, cnt_idx, e);
}