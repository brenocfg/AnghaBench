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
typedef  scalar_t__ ns_sect ;

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  NS_GET16 (int,unsigned char const*) ; 
 int NS_INT16SZ ; 
 int NS_INT32SZ ; 
 int dn_skipname (unsigned char const*,unsigned char const*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ns_s_qd ; 

int ns_skiprr(const unsigned char *ptr, const unsigned char *eom, ns_sect section, int count)
{
	const unsigned char *p = ptr;
	int r;

	while (count--) {
		r = dn_skipname(p, eom);
		if (r < 0) goto bad;
		if (r + 2 * NS_INT16SZ > eom - p) goto bad;
		p += r + 2 * NS_INT16SZ;
		if (section != ns_s_qd) {
			if (NS_INT32SZ + NS_INT16SZ > eom - p) goto bad;
			p += NS_INT32SZ;
			NS_GET16(r, p);
			if (r > eom - p) goto bad;
			p += r;
		}
	}
	return p - ptr;
bad:
	errno = EMSGSIZE;
	return -1;
}