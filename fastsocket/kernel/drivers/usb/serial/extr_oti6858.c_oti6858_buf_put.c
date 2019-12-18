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
struct oti6858_buf {unsigned int buf_buf; unsigned int buf_size; unsigned int buf_put; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned int,char const*,unsigned int) ; 
 unsigned int oti6858_buf_space_avail (struct oti6858_buf*) ; 

__attribute__((used)) static unsigned int oti6858_buf_put(struct oti6858_buf *pb, const char *buf,
					unsigned int count)
{
	unsigned int len;

	if (pb == NULL)
		return 0;

	len  = oti6858_buf_space_avail(pb);
	if (count > len)
		count = len;

	if (count == 0)
		return 0;

	len = pb->buf_buf + pb->buf_size - pb->buf_put;
	if (count > len) {
		memcpy(pb->buf_put, buf, len);
		memcpy(pb->buf_buf, buf+len, count - len);
		pb->buf_put = pb->buf_buf + count - len;
	} else {
		memcpy(pb->buf_put, buf, count);
		if (count < len)
			pb->buf_put += count;
		else /* count == len */
			pb->buf_put = pb->buf_buf;
	}

	return count;
}