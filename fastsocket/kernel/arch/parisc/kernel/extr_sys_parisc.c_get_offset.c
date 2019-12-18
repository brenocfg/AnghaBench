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
struct address_space {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 

__attribute__((used)) static int get_offset(struct address_space *mapping)
{
	int offset = (unsigned long) mapping << (PAGE_SHIFT - 8);
	return offset & 0x3FF000;
}