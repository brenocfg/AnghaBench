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
 int BR_EC_secp256r1 ; 
 int get_curve_by_name (char const*) ; 

__attribute__((used)) static int
parse_ec_spec(const char *kgen_spec, int *curve)
{
	const char *p;

	*curve = 0;
	p = kgen_spec;
	if (*p != 'e' && *p != 'E') {
		return 0;
	}
	p ++;
	if (*p != 'c' && *p != 'C') {
		return 0;
	}
	p ++;
	if (*p == 0) {
		*curve = BR_EC_secp256r1;
		return 1;
	}
	if (*p != ':') {
		return 0;
	}
	*curve = get_curve_by_name(p);
	return *curve > 0;
}