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
struct egpio_info {int reg_shift; } ;

/* Variables and functions */

__attribute__((used)) static inline int egpio_pos(struct egpio_info *ei, int bit)
{
	return bit >> ei->reg_shift;
}