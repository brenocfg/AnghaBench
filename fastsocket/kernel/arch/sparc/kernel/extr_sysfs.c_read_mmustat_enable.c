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
 int /*<<< orphan*/  sun4v_mmustat_info (unsigned long*) ; 

__attribute__((used)) static unsigned long read_mmustat_enable(unsigned long junk)
{
	unsigned long ra = 0;

	sun4v_mmustat_info(&ra);

	return ra != 0;
}