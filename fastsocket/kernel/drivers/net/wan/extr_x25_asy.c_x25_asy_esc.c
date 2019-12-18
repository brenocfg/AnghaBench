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

/* Variables and functions */
#define  X25_END 129 
#define  X25_ESC 128 
 void* X25_ESCAPE (int const) ; 

__attribute__((used)) static int x25_asy_esc(unsigned char *s, unsigned char *d, int len)
{
	unsigned char *ptr = d;
	unsigned char c;

	/*
	 * Send an initial END character to flush out any
	 * data that may have accumulated in the receiver
	 * due to line noise.
	 */

	*ptr++ = X25_END;	/* Send 10111110 bit seq */

	/*
	 * For each byte in the packet, send the appropriate
	 * character sequence, according to the X.25 protocol.
	 */

	while (len-- > 0) {
		switch (c = *s++) {
		case X25_END:
			*ptr++ = X25_ESC;
			*ptr++ = X25_ESCAPE(X25_END);
			break;
		case X25_ESC:
			*ptr++ = X25_ESC;
			*ptr++ = X25_ESCAPE(X25_ESC);
			break;
		default:
			*ptr++ = c;
			break;
		}
	}
	*ptr++ = X25_END;
	return (ptr - d);
}