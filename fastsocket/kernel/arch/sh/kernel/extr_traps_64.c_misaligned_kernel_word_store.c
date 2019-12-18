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
typedef  unsigned short __u16 ;

/* Variables and functions */

__attribute__((used)) static void misaligned_kernel_word_store(__u64 address, __u64 value)
{
	unsigned short x;
	unsigned char *p, *q;
	p = (unsigned char *) (int) address;
	q = (unsigned char *) &x;

	x = (__u16) value;
	p[0] = q[0];
	p[1] = q[1];
}