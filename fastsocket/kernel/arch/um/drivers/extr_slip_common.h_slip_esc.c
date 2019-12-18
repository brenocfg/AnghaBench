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
#define  SLIP_END 129 
#define  SLIP_ESC 128 
 int /*<<< orphan*/  SLIP_ESC_END ; 
 int /*<<< orphan*/  SLIP_ESC_ESC ; 

__attribute__((used)) static inline int slip_esc(unsigned char *s, unsigned char *d, int len)
{
	unsigned char *ptr = d;
	unsigned char c;

	/*
	 * Send an initial END character to flush out any
	 * data that may have accumulated in the receiver
	 * due to line noise.
	 */

	*ptr++ = SLIP_END;

	/*
	 * For each byte in the packet, send the appropriate
	 * character sequence, according to the SLIP protocol.
	 */

	while (len-- > 0) {
		switch(c = *s++) {
		case SLIP_END:
			*ptr++ = SLIP_ESC;
			*ptr++ = SLIP_ESC_END;
			break;
		case SLIP_ESC:
			*ptr++ = SLIP_ESC;
			*ptr++ = SLIP_ESC_ESC;
			break;
		default:
			*ptr++ = c;
			break;
		}
	}
	*ptr++ = SLIP_END;
	return (ptr - d);
}