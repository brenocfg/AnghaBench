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
typedef  int /*<<< orphan*/  compat_clock_t ;
typedef  int /*<<< orphan*/  clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  clock_t_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compat_jiffies_to_clock_t (int /*<<< orphan*/ ) ; 

__attribute__((used)) static compat_clock_t clock_t_to_compat_clock_t(clock_t x)
{
	return compat_jiffies_to_clock_t(clock_t_to_jiffies(x));
}