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
typedef  int /*<<< orphan*/  smd_channel_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ch_is_open (int /*<<< orphan*/ *) ; 
 unsigned int ch_write_buffer (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ch_write_done (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memcpy (void*,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  notify_other_smd () ; 

__attribute__((used)) static int smd_stream_write(smd_channel_t *ch, const void *_data, int len)
{
	void *ptr;
	const unsigned char *buf = _data;
	unsigned xfer;
	int orig_len = len;

	if (len < 0)
		return -EINVAL;

	while ((xfer = ch_write_buffer(ch, &ptr)) != 0) {
		if (!ch_is_open(ch))
			break;
		if (xfer > len)
			xfer = len;
		memcpy(ptr, buf, xfer);
		ch_write_done(ch, xfer);
		len -= xfer;
		buf += xfer;
		if (len == 0)
			break;
	}

	notify_other_smd();

	return orig_len - len;
}