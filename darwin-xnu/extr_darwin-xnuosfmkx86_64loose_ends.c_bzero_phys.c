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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  addr64_t ;

/* Variables and functions */
 int /*<<< orphan*/  PHYSMAP_PTOV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bzero_phys(
	   addr64_t src64,
	   uint32_t bytes)
{
	bzero(PHYSMAP_PTOV(src64), bytes);
}