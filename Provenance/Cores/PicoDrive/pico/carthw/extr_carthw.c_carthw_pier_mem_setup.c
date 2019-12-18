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
 int /*<<< orphan*/  carthw_pier_read8 ; 
 int /*<<< orphan*/  carthw_pier_write16 ; 
 int /*<<< orphan*/  carthw_pier_write8 ; 
 int /*<<< orphan*/  cpu68k_map_set (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m68k_read8_map ; 
 int /*<<< orphan*/  m68k_write16_map ; 
 int /*<<< orphan*/  m68k_write8_map ; 

__attribute__((used)) static void carthw_pier_mem_setup(void)
{
  cpu68k_map_set(m68k_write8_map,  0xa10000, 0xa1ffff, carthw_pier_write8, 1);
  cpu68k_map_set(m68k_write16_map, 0xa10000, 0xa1ffff, carthw_pier_write16, 1);
  cpu68k_map_set(m68k_read8_map,   0xa10000, 0xa1ffff, carthw_pier_read8, 1);
}