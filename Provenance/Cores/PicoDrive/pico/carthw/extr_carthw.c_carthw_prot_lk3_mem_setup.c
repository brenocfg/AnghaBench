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
 int /*<<< orphan*/  PicoRead8_plk3 ; 
 int /*<<< orphan*/  PicoWrite8_plk3b ; 
 int /*<<< orphan*/  PicoWrite8_plk3p ; 
 int /*<<< orphan*/  cpu68k_map_set (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m68k_read8_map ; 
 int /*<<< orphan*/  m68k_write8_map ; 

__attribute__((used)) static void carthw_prot_lk3_mem_setup(void)
{
  cpu68k_map_set(m68k_read8_map,   0x600000, 0x7fffff, PicoRead8_plk3, 1);
  cpu68k_map_set(m68k_write8_map,  0x600000, 0x6fffff, PicoWrite8_plk3p, 1);
  cpu68k_map_set(m68k_write8_map,  0x700000, 0x7fffff, PicoWrite8_plk3b, 1);
}