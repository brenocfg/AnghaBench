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
struct kernel_param {scalar_t__ arg; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int MAX_HASHTABLE_BITS ; 
 unsigned int fls (unsigned long) ; 
 int strict_strtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int param_set_hashtbl_sz(const char *val, struct kernel_param *kp)
{
	unsigned long num;
	unsigned int nbits;
	int ret;

	if (!val)
		goto out_inval;
	ret = strict_strtoul(val, 0, &num);
	if (ret == -EINVAL)
		goto out_inval;
	nbits = fls(num);
	if (num > (1U << nbits))
		nbits++;
	if (nbits > MAX_HASHTABLE_BITS || nbits < 2)
		goto out_inval;
	*(unsigned int *)kp->arg = nbits;
	return 0;
out_inval:
	return -EINVAL;
}