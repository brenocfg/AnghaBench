#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t ring_head; size_t ring_tail; TYPE_1__* ring; } ;
struct ar9170 {TYPE_2__ debug; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,int /*<<< orphan*/ ,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t CARL9170_DEBUG_RING_SIZE ; 

__attribute__((used)) static char *carl9170_debugfs_hw_ioread32_read(struct ar9170 *ar, char *buf,
					       size_t bufsize, ssize_t *ret)
{
	int i = 0;

	while (ar->debug.ring_head != ar->debug.ring_tail) {
		ADD(buf, *ret, bufsize, "%.8x = %.8x\n",
		    ar->debug.ring[ar->debug.ring_head].reg,
		    ar->debug.ring[ar->debug.ring_head].value);

		ar->debug.ring_head++;
		ar->debug.ring_head %= CARL9170_DEBUG_RING_SIZE;

		if (i++ == 64)
			break;
	}
	ar->debug.ring_head = ar->debug.ring_tail;
	return buf;
}