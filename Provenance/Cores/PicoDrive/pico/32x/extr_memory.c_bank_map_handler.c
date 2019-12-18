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
 int /*<<< orphan*/  PicoRead16_bank ; 
 int /*<<< orphan*/  PicoRead8_bank ; 
 int /*<<< orphan*/  cpu68k_map_set (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m68k_read16_map ; 
 int /*<<< orphan*/  m68k_read8_map ; 

__attribute__((used)) static void bank_map_handler(void)
{
  cpu68k_map_set(m68k_read8_map,   0x900000, 0x9fffff, PicoRead8_bank, 1);
  cpu68k_map_set(m68k_read16_map,  0x900000, 0x9fffff, PicoRead16_bank, 1);
}