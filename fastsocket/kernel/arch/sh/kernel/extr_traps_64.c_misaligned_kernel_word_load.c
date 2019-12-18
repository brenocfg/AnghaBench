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
typedef  scalar_t__ __u64 ;
typedef  scalar_t__ __s64 ;

/* Variables and functions */

__attribute__((used)) static void misaligned_kernel_word_load(__u64 address, int do_sign_extend, __u64 *result)
{
	unsigned short x;
	unsigned char *p, *q;
	p = (unsigned char *) (int) address;
	q = (unsigned char *) &x;
	q[0] = p[0];
	q[1] = p[1];

	if (do_sign_extend) {
		*result = (__u64)(__s64) *(short *) &x;
	} else {
		*result = (__u64) x;
	}
}