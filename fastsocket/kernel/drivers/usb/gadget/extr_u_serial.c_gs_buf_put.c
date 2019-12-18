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
struct gs_buf {unsigned int buf_buf; unsigned int buf_size; unsigned int buf_put; } ;

/* Variables and functions */
 unsigned int gs_buf_space_avail (struct gs_buf*) ; 
 int /*<<< orphan*/  memcpy (unsigned int,char const*,unsigned int) ; 

__attribute__((used)) static unsigned
gs_buf_put(struct gs_buf *gb, const char *buf, unsigned count)
{
	unsigned len;

	len  = gs_buf_space_avail(gb);
	if (count > len)
		count = len;

	if (count == 0)
		return 0;

	len = gb->buf_buf + gb->buf_size - gb->buf_put;
	if (count > len) {
		memcpy(gb->buf_put, buf, len);
		memcpy(gb->buf_buf, buf+len, count - len);
		gb->buf_put = gb->buf_buf + count - len;
	} else {
		memcpy(gb->buf_put, buf, count);
		if (count < len)
			gb->buf_put += count;
		else /* count == len */
			gb->buf_put = gb->buf_buf;
	}

	return count;
}