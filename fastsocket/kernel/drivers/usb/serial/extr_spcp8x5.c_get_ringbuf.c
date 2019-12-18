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
struct ringbuf {unsigned int buf_buf; unsigned int buf_size; unsigned int buf_get; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,unsigned int,unsigned int) ; 
 unsigned int ringbuf_avail_data (struct ringbuf*) ; 

__attribute__((used)) static unsigned int get_ringbuf(struct ringbuf *pb, char *buf,
				unsigned int count)
{
	unsigned int len;

	if (pb == NULL || buf == NULL)
		return 0;

	len = ringbuf_avail_data(pb);
	if (count > len)
		count = len;

	if (count == 0)
		return 0;

	len = pb->buf_buf + pb->buf_size - pb->buf_get;
	if (count > len) {
		memcpy(buf, pb->buf_get, len);
		memcpy(buf+len, pb->buf_buf, count - len);
		pb->buf_get = pb->buf_buf + count - len;
	} else {
		memcpy(buf, pb->buf_get, count);
		if (count < len)
			pb->buf_get += count;
		else /* count == len */
			pb->buf_get = pb->buf_buf;
	}

	return count;
}