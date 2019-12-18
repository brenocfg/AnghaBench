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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ztest_random (int) ; 

__attribute__((used)) static nvlist_t *
make_random_props()
{
	nvlist_t *props;

	VERIFY(nvlist_alloc(&props, NV_UNIQUE_NAME, 0) == 0);
	if (ztest_random(2) == 0)
		return (props);
	VERIFY(nvlist_add_uint64(props, "autoreplace", 1) == 0);

	return (props);
}