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
 int __card_rand () ; 
 int /*<<< orphan*/  __card_srand (int) ; 
 int gettick () ; 

__attribute__((used)) static u32 __card_initval()
{
	u32 ticks = gettick();

	__card_srand(ticks);
	return ((0x7FEC8000|__card_rand())&~0x00000fff);
}