#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct memory_accessor {scalar_t__ (* read ) (struct memory_accessor*,char*,int /*<<< orphan*/ ,scalar_t__) ;} ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_4__ {TYPE_1__* emac_pdata; } ;
struct TYPE_3__ {char* mac_addr; } ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 TYPE_2__ davinci_soc_info ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 scalar_t__ stub1 (struct memory_accessor*,char*,int /*<<< orphan*/ ,scalar_t__) ; 

void davinci_get_mac_addr(struct memory_accessor *mem_acc, void *context)
{
	char *mac_addr = davinci_soc_info.emac_pdata->mac_addr;
	off_t offset = (off_t)context;

	/* Read MAC addr from EEPROM */
	if (mem_acc->read(mem_acc, mac_addr, offset, ETH_ALEN) == ETH_ALEN)
		pr_info("Read MAC addr from EEPROM: %pM\n", mac_addr);
}