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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 scalar_t__ FLASH_MAC ; 
 int /*<<< orphan*/  bfin_read16 (scalar_t__) ; 
 int /*<<< orphan*/  bfin_read32 (scalar_t__) ; 

void bfin_get_ether_addr(char *addr)
{
	*(u32 *)(&(addr[0])) = bfin_read32(FLASH_MAC);
	*(u16 *)(&(addr[4])) = bfin_read16(FLASH_MAC + 4);
}