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
typedef  int uint32_t ;

/* Variables and functions */
 unsigned long strtoul (char const*,char**,int) ; 

__attribute__((used)) static int
parse_rsa_spec(const char *kgen_spec, unsigned *size, uint32_t *pubexp)
{
	const char *p;
	char *end;
	unsigned long ul;

	p = kgen_spec;
	if (*p != 'r' && *p != 'R') {
		return 0;
	}
	p ++;
	if (*p != 's' && *p != 'S') {
		return 0;
	}
	p ++;
	if (*p != 'a' && *p != 'A') {
		return 0;
	}
	p ++;
	if (*p == 0) {
		*size = 2048;
		*pubexp = 3;
		return 1;
	} else if (*p != ':') {
		return 0;
	}
	p ++;
	ul = strtoul(p, &end, 10);
	if (ul < 512 || ul > 32768) {
		return 0;
	}
	*size = ul;
	p = end;
	if (*p == 0) {
		*pubexp = 3;
		return 1;
	} else if (*p != ':') {
		return 0;
	}
	p ++;
	ul = strtoul(p, &end, 10);
	if ((ul & 1) == 0 || ul == 1 || ((ul >> 30) >> 2) != 0) {
		return 0;
	}
	*pubexp = ul;
	if (*end != 0) {
		return 0;
	}
	return 1;
}