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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  bridge_base ; 
 int /*<<< orphan*/  c2k_bridge_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv64x60_get_mem_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void c2k_fixups(void)
{
	u32 mem_size;

	mem_size = mv64x60_get_mem_size(bridge_base);
	c2k_bridge_setup(mem_size); /* Do necessary bridge setup */
}