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
typedef  scalar_t__ u_int8_t ;
typedef  int u_int32_t ;
typedef  int u_int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGNED16 (void const*) ; 
 scalar_t__ ALIGNED32 (void const*) ; 
 int /*<<< orphan*/  JHASH_FINAL (int,int,int) ; 
 int const JHASH_INIT ; 
 int /*<<< orphan*/  JHASH_MIX (int,int,int) ; 

u_int32_t
net_flowhash_jhash(const void *key, u_int32_t len, const u_int32_t seed)
{
	u_int32_t a, b, c;

	/* Set up the internal state */
	a = b = c = JHASH_INIT + len + seed;

#if defined(__i386__) || defined(__x86_64__)
	/*
	 * On i386/x86_64, it is faster to read 32-bit chunks if the key
	 * is aligned 32-bit OR not 16-bit, and perform 16-bit reads if it
	 * is aligned 16-bit.
	 */
	if (ALIGNED32(key) || !ALIGNED16(key)) {
#else /* !defined(__i386__) && !defined(__x86_64__) */
	if (ALIGNED32(key)) {
#endif /* !defined(__i386__) && !defined(__x86_64__) */
		/* read 32-bit chunks */
		const u_int32_t *k = (const u_int32_t *)key;

		/*
		 * all but last block:
		 * aligned reads and affect 32 bits of (a,b,c)
		 */
		while (len > 12) {
			a += k[0];
			b += k[1];
			c += k[2];
			JHASH_MIX(a, b, c);
			len -= 12;
			k += 3;
		}

		/*
		 * handle the last (probably partial) block
		 *
		 * "k[2] & 0xffffff" actually reads beyond the end of the
		 * string, but then masks off the part it's not allowed
		 * to read.  Because the string is aligned, the masked-off
		 * tail is in the same word as the rest of the string.
		 * The masking trick does make the hash noticably faster
		 * for short strings (like English words).
		 */
		switch (len) {
		case 12:
			c += k[2];
			b += k[1];
			a += k[0];
			break;

		case 11:
			c += k[2] & 0xffffff;
			b += k[1];
			a += k[0];
			break;

		case 10:
			c += k[2] & 0xffff;
			b += k[1];
			a += k[0];
			break;

		case 9:
			c += k[2] & 0xff;
			b += k[1];
			a += k[0];
			break;

		case 8:
			b += k[1];
			a += k[0];
			break;

		case 7:
			b += k[1] & 0xffffff;
			a += k[0];
			break;

		case 6:
			b += k[1] & 0xffff;
			a += k[0];
			break;

		case 5:
			b += k[1] & 0xff;
			a += k[0];
			break;

		case 4:
			a += k[0];
			break;

		case 3:
			a += k[0] & 0xffffff;
			break;

		case 2:
			a += k[0] & 0xffff;
			break;

		case 1:
			a += k[0] & 0xff;
			break;

		case 0:
			/* zero length requires no mixing */
			return (c);
		}

		JHASH_FINAL(a, b, c);

		return (c);
	}
#if !defined(__i386__) && !defined(__x86_64__)
	else if (ALIGNED16(key)) {
#endif /* !defined(__i386__) && !defined(__x86_64__) */
		/* read 16-bit chunks */
		const u_int16_t *k = (const u_int16_t *)key;
		const u_int8_t *k8;

		/* all but last block: aligned reads and different mixing */
		while (len > 12) {
			a += k[0] + (((u_int32_t)k[1]) << 16);
			b += k[2] + (((u_int32_t)k[3]) << 16);
			c += k[4] + (((u_int32_t)k[5]) << 16);
			JHASH_MIX(a, b, c);
			len -= 12;
			k += 6;
		}

		/* handle the last (probably partial) block */
		k8 = (const u_int8_t *)k;
		switch (len) {
		case 12:
			c += k[4] + (((u_int32_t)k[5]) << 16);
			b += k[2] + (((u_int32_t)k[3]) << 16);
			a += k[0] + (((u_int32_t)k[1]) << 16);
			break;

		case 11:
			c += ((u_int32_t)k8[10]) << 16;
			/* FALLTHRU */
		case 10:
			c += k[4];
			b += k[2] + (((u_int32_t)k[3]) << 16);
			a += k[0] + (((u_int32_t)k[1]) << 16);
			break;

		case 9:
			c += k8[8];
			/* FALLTHRU */
		case 8:
			b += k[2] + (((u_int32_t)k[3]) << 16);
			a += k[0] + (((u_int32_t)k[1]) << 16);
			break;

		case 7:
			b += ((u_int32_t)k8[6]) << 16;
			/* FALLTHRU */
		case 6:
			b += k[2];
			a += k[0] + (((u_int32_t)k[1]) << 16);
			break;

		case 5:
			b += k8[4];
			/* FALLTHRU */
		case 4:
			a += k[0] + (((u_int32_t)k[1]) << 16);
			break;

		case 3:
			a += ((u_int32_t)k8[2]) << 16;
			/* FALLTHRU */
		case 2:
			a += k[0];
			break;

		case 1:
			a += k8[0];
			break;

		case 0:
			/* zero length requires no mixing */
			return (c);
		}

		JHASH_FINAL(a, b, c);

		return (c);
#if !defined(__i386__) && !defined(__x86_64__)
	}

	/* need to read the key one byte at a time */
	const u_int8_t *k = (const u_int8_t *)key;

	/* all but the last block: affect some 32 bits of (a,b,c) */
	while (len > 12) {
		a += k[0];
		a += ((u_int32_t)k[1]) << 8;
		a += ((u_int32_t)k[2]) << 16;
		a += ((u_int32_t)k[3]) << 24;
		b += k[4];
		b += ((u_int32_t)k[5]) << 8;
		b += ((u_int32_t)k[6]) << 16;
		b += ((u_int32_t)k[7]) << 24;
		c += k[8];
		c += ((u_int32_t)k[9]) << 8;
		c += ((u_int32_t)k[10]) << 16;
		c += ((u_int32_t)k[11]) << 24;
		JHASH_MIX(a, b, c);
		len -= 12;
		k += 12;
	}

	/* last block: affect all 32 bits of (c) */
	switch (len) {
	case 12:
		c += ((u_int32_t)k[11]) << 24;
		/* FALLTHRU */
	case 11:
		c += ((u_int32_t)k[10]) << 16;
		/* FALLTHRU */
	case 10:
		c += ((u_int32_t)k[9]) << 8;
		/* FALLTHRU */
	case 9:
		c += k[8];
		/* FALLTHRU */
	case 8:
		b += ((u_int32_t)k[7]) << 24;
		/* FALLTHRU */
	case 7:
		b += ((u_int32_t)k[6]) << 16;
		/* FALLTHRU */
	case 6:
		b += ((u_int32_t)k[5]) << 8;
		/* FALLTHRU */
	case 5:
		b += k[4];
		/* FALLTHRU */
	case 4:
		a += ((u_int32_t)k[3]) << 24;
		/* FALLTHRU */
	case 3:
		a += ((u_int32_t)k[2]) << 16;
		/* FALLTHRU */
	case 2:
		a += ((u_int32_t)k[1]) << 8;
		/* FALLTHRU */
	case 1:
		a += k[0];
		break;

	case 0:
		/* zero length requires no mixing */
		return (c);
	}

	JHASH_FINAL(a, b, c);

	return (c);
#endif /* !defined(__i386__) && !defined(__x86_64__) */
}