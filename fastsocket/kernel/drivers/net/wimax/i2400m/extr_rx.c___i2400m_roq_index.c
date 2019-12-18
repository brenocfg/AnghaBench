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
struct i2400m_roq {int dummy; } ;
struct i2400m {scalar_t__ rx_roq; } ;

/* Variables and functions */

__attribute__((used)) static
unsigned __i2400m_roq_index(struct i2400m *i2400m, struct i2400m_roq *roq)
{
	return ((unsigned long) roq - (unsigned long) i2400m->rx_roq)
		/ sizeof(*roq);
}