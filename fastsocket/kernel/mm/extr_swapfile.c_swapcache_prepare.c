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
typedef  int /*<<< orphan*/  swp_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP_HAS_CACHE ; 
 int __swap_duplicate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int swapcache_prepare(swp_entry_t entry)
{
	return __swap_duplicate(entry, SWAP_HAS_CACHE);
}