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
 int /*<<< orphan*/  BUG () ; 

__attribute__((used)) static unsigned long index_to_divisor(unsigned int index)
{
	switch (index) {
	case 0:
		return 1;

	case 1:
		return 2;

	case 2:
		return 4;

	case 3:
		return 6;

	case 4:
		return 8;

	default:
		BUG();
	};
}