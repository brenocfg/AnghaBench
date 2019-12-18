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
typedef  scalar_t__ const u8 ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_PORTSC ; 
 int EINVAL ; 
 int /*<<< orphan*/  PORTSC_PTC ; 
 scalar_t__ const ffs_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_cwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__ const) ; 

__attribute__((used)) static int hw_port_test_set(u8 mode)
{
	const u8 TEST_MODE_MAX = 7;

	if (mode > TEST_MODE_MAX)
		return -EINVAL;

	hw_cwrite(CAP_PORTSC, PORTSC_PTC, mode << ffs_nr(PORTSC_PTC));
	return 0;
}