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
 int AC97_LINK_FRAME ; 
 scalar_t__* delay_table ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

__attribute__((used)) static inline void poll_delay(int d)
{
	udelay(3 * AC97_LINK_FRAME + delay_table[d]);
}