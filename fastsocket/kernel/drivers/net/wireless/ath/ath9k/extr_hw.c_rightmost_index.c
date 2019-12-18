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
struct ath_gen_timer_table {int* gen_timer_index; } ;

/* Variables and functions */
 int debruijn32 ; 

__attribute__((used)) static u32 rightmost_index(struct ath_gen_timer_table *timer_table, u32 *mask)
{
	u32 b;

	b = *mask;
	b &= (0-b);
	*mask &= ~b;
	b *= debruijn32;
	b >>= 27;

	return timer_table->gen_timer_index[b];
}