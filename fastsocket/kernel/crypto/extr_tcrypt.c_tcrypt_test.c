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
 int EINVAL ; 
 int alg_test (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fips_enabled ; 

__attribute__((used)) static inline int tcrypt_test(const char *alg)
{
	int ret;

	ret = alg_test(alg, alg, 0, 0);
	/* non-fips algs return -EINVAL in fips mode */
	if (fips_enabled && ret == -EINVAL)
		ret = 0;
	return ret;
}