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
typedef  enum debuglevel { ____Placeholder_debuglevel } debuglevel ;

/* Variables and functions */
 int /*<<< orphan*/  gig_dbg (int,char*,unsigned char const*,unsigned int,unsigned char*) ; 

void gigaset_dbg_buffer(enum debuglevel level, const unsigned char *msg,
			size_t len, const unsigned char *buf)
{
	unsigned char outbuf[80];
	unsigned char c;
	size_t space = sizeof outbuf - 1;
	unsigned char *out = outbuf;
	size_t numin = len;

	while (numin--) {
		c = *buf++;
		if (c == '~' || c == '^' || c == '\\') {
			if (!space--)
				break;
			*out++ = '\\';
		}
		if (c & 0x80) {
			if (!space--)
				break;
			*out++ = '~';
			c ^= 0x80;
		}
		if (c < 0x20 || c == 0x7f) {
			if (!space--)
				break;
			*out++ = '^';
			c ^= 0x40;
		}
		if (!space--)
			break;
		*out++ = c;
	}
	*out = 0;

	gig_dbg(level, "%s (%u bytes): %s", msg, (unsigned) len, outbuf);
}