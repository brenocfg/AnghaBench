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
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish ; 

__attribute__((used)) static inline void stop_timing(void)
{
	do_gettimeofday(&finish);
}