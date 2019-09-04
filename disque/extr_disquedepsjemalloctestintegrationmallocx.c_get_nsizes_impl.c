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
 int /*<<< orphan*/  assert_d_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  mallctl (char const*,unsigned int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
get_nsizes_impl(const char *cmd)
{
	unsigned ret;
	size_t z;

	z = sizeof(unsigned);
	assert_d_eq(mallctl(cmd, &ret, &z, NULL, 0), 0,
	    "Unexpected mallctl(\"%s\", ...) failure", cmd);

	return (ret);
}