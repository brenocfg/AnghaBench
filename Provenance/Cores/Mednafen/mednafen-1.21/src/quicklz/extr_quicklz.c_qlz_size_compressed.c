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
 unsigned int fast_read (char const*,unsigned int) ; 

size_t qlz_size_compressed(const char *source)
{
	unsigned int n, r;
	n = (((*source) & 2) == 2) ? 4 : 1;
	r = fast_read(source + 1, n);
	r = r & (0xffffffff >> ((4 - n)*8));
	return r;
}