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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT_PERF_HASH_SEED ; 
 int UNIT_PERF_SLOT_MASK ; 
 int jhash (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static u32 get_point_index(const char *name)
{
#define UNIT_PERF_HASH_SEED		(*((u32*)"uphs"))

	u32 value = jhash(name, strlen(name), UNIT_PERF_HASH_SEED);

	return (value&UNIT_PERF_SLOT_MASK);
}