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
 int E2BIG ; 
 int EINVAL ; 
 int EOVERFLOW ; 
 size_t RSIZE_MAX ; 
 int /*<<< orphan*/  secure_memset (void*,int,size_t) ; 

int
memset_s(void *s, size_t smax, int c, size_t n)
{
	int err = 0;

	if (s == NULL) return EINVAL;
	if (smax > RSIZE_MAX) return E2BIG;
	if (n > smax) {
		n = smax;
		err = EOVERFLOW;
	}

	/* 
	 * secure_memset is defined in assembly, we therefore
 	 * expect that the compiler will not inline the call.
	 */
	secure_memset(s, c, n);

	return err;
}