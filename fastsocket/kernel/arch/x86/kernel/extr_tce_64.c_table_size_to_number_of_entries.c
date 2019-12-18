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

__attribute__((used)) static inline unsigned int table_size_to_number_of_entries(unsigned char size)
{
	/*
	 * size is the order of the table, 0-7
	 * smallest table is 8K entries, so shift result by 13 to
	 * multiply by 8K
	 */
	return (1 << size) << 13;
}