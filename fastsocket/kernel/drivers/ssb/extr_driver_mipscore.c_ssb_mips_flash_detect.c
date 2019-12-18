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
struct ssb_mipscore {int flash_buswidth; int flash_window; int flash_window_size; TYPE_1__* dev; } ;
struct TYPE_4__ {scalar_t__ dev; } ;
struct ssb_bus {TYPE_2__ chipco; } ;
struct TYPE_3__ {struct ssb_bus* bus; } ;

/* Variables and functions */
 int SSB_CHIPCO_CFG_DS16 ; 
 int /*<<< orphan*/  SSB_CHIPCO_FLASH_CFG ; 
 int ssb_read32 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssb_mips_flash_detect(struct ssb_mipscore *mcore)
{
	struct ssb_bus *bus = mcore->dev->bus;

	mcore->flash_buswidth = 2;
	if (bus->chipco.dev) {
		mcore->flash_window = 0x1c000000;
		mcore->flash_window_size = 0x02000000;
		if ((ssb_read32(bus->chipco.dev, SSB_CHIPCO_FLASH_CFG)
		               & SSB_CHIPCO_CFG_DS16) == 0)
			mcore->flash_buswidth = 1;
	} else {
		mcore->flash_window = 0x1fc00000;
		mcore->flash_window_size = 0x00400000;
	}
}