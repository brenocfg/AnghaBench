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
 int /*<<< orphan*/  T_SKIP (char*) ; 
 int _get_cpu_capabilities () ; 
 int kHasAVX512F ; 

void
require_avx512(void) {
	if((_get_cpu_capabilities() & kHasAVX512F) != kHasAVX512F) {
		T_SKIP("AVX-512 not supported on this system");
	}
}