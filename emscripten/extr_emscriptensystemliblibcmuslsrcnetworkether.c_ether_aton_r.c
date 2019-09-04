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
struct ether_addr {unsigned long* ether_addr_octet; } ;

/* Variables and functions */
 unsigned long strtoul (char const*,char**,int) ; 

struct ether_addr *ether_aton_r (const char *x, struct ether_addr *p_a)
{
	struct ether_addr a;
	char *y;
	for (int ii = 0; ii < 6; ii++) {
		unsigned long int n;
		if (ii != 0) {
			if (x[0] != ':') return 0; /* bad format */
			else x++;
		}
		n = strtoul (x, &y, 16);
		x = y;
		if (n > 0xFF) return 0; /* bad byte */
		a.ether_addr_octet[ii] = n;
	}
	if (x[0] != 0) return 0; /* bad format */
	*p_a = a;
	return p_a;
}