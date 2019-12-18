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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  expand_overloaded_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_raw ; 
 int /*<<< orphan*/  well_known_flags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t kpageflags_flags(uint64_t flags)
{
	flags = expand_overloaded_flags(flags);

	if (!opt_raw)
		flags = well_known_flags(flags);

	return flags;
}