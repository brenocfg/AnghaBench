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
typedef  int /*<<< orphan*/  br_ec_impl ;
typedef  int /*<<< orphan*/  br_ec_curve_def ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int /*<<< orphan*/  test_speed_ec_inner_1 (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  test_speed_ec_inner_2 (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
test_speed_ec_inner(const char *name,
	const br_ec_impl *impl, const br_ec_curve_def *cd)
{
	char tmp[50];

	test_speed_ec_inner_1(name, impl, cd);
	sprintf(tmp, "%s (FP)", name);
	test_speed_ec_inner_2(tmp, impl, cd);
}