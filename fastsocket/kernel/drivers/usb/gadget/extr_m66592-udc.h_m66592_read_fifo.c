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
struct m66592 {TYPE_1__* pdata; scalar_t__ reg; } ;
struct TYPE_2__ {scalar_t__ on_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  insl (unsigned long,void*,unsigned long) ; 
 int /*<<< orphan*/  insw (unsigned long,void*,unsigned long) ; 

__attribute__((used)) static inline void m66592_read_fifo(struct m66592 *m66592,
		unsigned long offset,
		void *buf, unsigned long len)
{
	unsigned long fifoaddr = (unsigned long)m66592->reg + offset;

	if (m66592->pdata->on_chip) {
		len = (len + 3) / 4;
		insl(fifoaddr, buf, len);
	} else {
		len = (len + 1) / 2;
		insw(fifoaddr, buf, len);
	}
}