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
struct dsa_switch {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  REG_GLOBAL ; 
 int REG_READ (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv88e6xxx_stats_wait(struct dsa_switch *ds)
{
	int ret;
	int i;

	for (i = 0; i < 10; i++) {
		ret = REG_READ(REG_GLOBAL, 0x1d);
		if ((ret & 0x8000) == 0)
			return 0;
	}

	return -ETIMEDOUT;
}