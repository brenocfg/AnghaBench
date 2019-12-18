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
struct circ_buf {int tail; scalar_t__ buf; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int CIRC_CNT_TO_END (int /*<<< orphan*/ ,int,int) ; 
 int TI_WRITE_BUF_SIZE ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 

__attribute__((used)) static int ti_buf_get(struct circ_buf *cb, char *buf, int count)
{
	int c, ret = 0;

	while (1) {
		c = CIRC_CNT_TO_END(cb->head, cb->tail, TI_WRITE_BUF_SIZE);
		if (count < c)
			c = count;
		if (c <= 0)
			break;
		memcpy(buf, cb->buf + cb->tail, c);
		cb->tail = (cb->tail + c) & (TI_WRITE_BUF_SIZE-1);
		buf += c;
		count -= c;
		ret += c;
	}

	return ret;
}