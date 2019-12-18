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
 int max (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cm_convert_to_ms(int iba_time)
{
	/* approximate conversion to ms from 4.096us x 2^iba_time */
	return 1 << max(iba_time - 8, 0);
}