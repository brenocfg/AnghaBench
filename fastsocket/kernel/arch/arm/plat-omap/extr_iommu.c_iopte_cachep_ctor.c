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
 int /*<<< orphan*/  IOPTE_TABLE_SIZE ; 
 int /*<<< orphan*/  clean_dcache_area (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iopte_cachep_ctor(void *iopte)
{
	clean_dcache_area(iopte, IOPTE_TABLE_SIZE);
}