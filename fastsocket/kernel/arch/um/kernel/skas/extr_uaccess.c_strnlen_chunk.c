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
 int strnlen (void*,int) ; 

__attribute__((used)) static int strnlen_chunk(unsigned long str, int len, void *arg)
{
	int *len_ptr = arg, n;

	n = strnlen((void *) str, len);
	*len_ptr += n;

	if (n < len)
		return 1;
	return 0;
}