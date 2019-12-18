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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int COL_WIDTH_BITS (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  debugf0 (char*,int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int numcol(u32 mtr)
{
	int cols = (COL_WIDTH_BITS(mtr) + 10);

	if (cols > 12) {
		debugf0("Invalid number of cols: %d (max = 4) raw value = %x (%04x)",
			cols, (unsigned int)COL_WIDTH_BITS(mtr), mtr);
		return -EINVAL;
	}

	return 1 << cols;
}