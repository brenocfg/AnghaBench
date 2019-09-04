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
typedef  int uint64_t ;

/* Variables and functions */
 int i ; 
 scalar_t__ j ; 
 int lcg64 (int) ; 
 int n ; 
 int* x ; 

__attribute__((used)) static void __srandom(unsigned seed) {
	int k;
	uint64_t s = seed;

	if (n == 0) {
		x[0] = s;
		return;
	}
	i = n == 31 || n == 7 ? 3 : 1;
	j = 0;
	for (k = 0; k < n; k++) {
		s = lcg64(s);
		x[k] = s>>32;
	}
	/* make sure x contains at least one odd number */
	x[0] |= 1;
}