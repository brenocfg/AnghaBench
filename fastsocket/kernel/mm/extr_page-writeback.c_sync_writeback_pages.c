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
 unsigned long ratelimit_pages ; 

__attribute__((used)) static inline long sync_writeback_pages(unsigned long dirtied)
{
	if (dirtied < ratelimit_pages)
		dirtied = ratelimit_pages;

	return dirtied + dirtied / 2;
}