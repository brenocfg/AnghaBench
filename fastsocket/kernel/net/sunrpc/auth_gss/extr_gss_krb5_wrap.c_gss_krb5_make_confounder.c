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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int random32 () ; 

void
gss_krb5_make_confounder(char *p, u32 conflen)
{
	static u64 i = 0;
	u64 *q = (u64 *)p;

	/* rfc1964 claims this should be "random".  But all that's really
	 * necessary is that it be unique.  And not even that is necessary in
	 * our case since our "gssapi" implementation exists only to support
	 * rpcsec_gss, so we know that the only buffers we will ever encrypt
	 * already begin with a unique sequence number.  Just to hedge my bets
	 * I'll make a half-hearted attempt at something unique, but ensuring
	 * uniqueness would mean worrying about atomicity and rollover, and I
	 * don't care enough. */

	/* initialize to random value */
	if (i == 0) {
		i = random32();
		i = (i << 32) | random32();
	}

	switch (conflen) {
	case 16:
		*q++ = i++;
		/* fall through */
	case 8:
		*q++ = i++;
		break;
	default:
		BUG();
	}
}