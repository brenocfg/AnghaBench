#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  bi_enet1addr; int /*<<< orphan*/  bi_enetaddr; } ;

/* Variables and functions */
 TYPE_1__ bd ; 
 int /*<<< orphan*/  dt_fixup_mac_addresses (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibm440ep_fixup_clocks (unsigned long,int,int) ; 
 int /*<<< orphan*/  ibm4xx_quiesce_eth (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibm4xx_sdram_fixup_memsize () ; 

__attribute__((used)) static void sam440ep_fixups(void)
{
       unsigned long sysclk = 66666666;

       ibm440ep_fixup_clocks(sysclk, 11059200, 25000000);
       ibm4xx_sdram_fixup_memsize();
       ibm4xx_quiesce_eth((u32 *)0xef600e00, (u32 *)0xef600f00);
       dt_fixup_mac_addresses(&bd.bi_enetaddr, &bd.bi_enet1addr);
}