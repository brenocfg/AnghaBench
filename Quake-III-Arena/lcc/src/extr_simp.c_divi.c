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
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static int divi(long x, long y, long min, long max, int needconst) {
	int cond = y != 0 && !(x == min && y == -1);
	if (!cond && needconst) {
		warning("overflow in constant expression\n");
		cond = 1;
	}
	return cond;


}