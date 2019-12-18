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
 int /*<<< orphan*/  HASHC ; 

long sdbm_hash(const char *str, int len)
{
	register unsigned long n = 0;

#define DUFF	/* go ahead and use the loop-unrolled version */
#ifdef DUFF

#define HASHC	n = *str++ + 65599 * n

	if (len > 0) {
		register int loop = (len + 8 - 1) >> 3;

		switch(len & (8 - 1)) {
		case 0:	do {
			HASHC;	case 7:	HASHC;
		case 6:	HASHC;	case 5:	HASHC;
		case 4:	HASHC;	case 3:	HASHC;
		case 2:	HASHC;	case 1:	HASHC;
			} while (--loop);
		}

	}
#else
	while (len--)
		n = *str++ + 65599 * n;
#endif
	return n;
}