#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned char generation; int /*<<< orphan*/  lock; TYPE_3__* rom; } ;
struct hpsb_host {TYPE_4__ csr; TYPE_2__* driver; } ;
typedef  int /*<<< orphan*/  quadlet_t ;
struct TYPE_7__ {int /*<<< orphan*/  bus_info_data; TYPE_1__* cache_head; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_hw_config_rom ) (struct hpsb_host*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {size_t size; size_t len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPSB_NOTICE (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct hpsb_host*,int /*<<< orphan*/ ) ; 

int hpsb_update_config_rom(struct hpsb_host *host, const quadlet_t *new_rom,
	size_t buffersize, unsigned char rom_version)
{
	unsigned long flags;
	int ret;

	HPSB_NOTICE("hpsb_update_config_rom() is deprecated");

        spin_lock_irqsave(&host->csr.lock, flags);
	if (rom_version != host->csr.generation)
                ret = -1;
	else if (buffersize > host->csr.rom->cache_head->size)
		ret = -2;
        else {
		/* Just overwrite the generated ConfigROM image with new data,
		 * it can be regenerated later. */
		memcpy(host->csr.rom->cache_head->data, new_rom, buffersize);
		host->csr.rom->cache_head->len = buffersize;

		if (host->driver->set_hw_config_rom)
			host->driver->set_hw_config_rom(host, host->csr.rom->bus_info_data);
		/* Increment the generation number to keep some sort of sync
		 * with the newer ConfigROM manipulation method. */
		host->csr.generation++;
		if (host->csr.generation > 0xf || host->csr.generation < 2)
			host->csr.generation = 2;
		ret=0;
        }
        spin_unlock_irqrestore(&host->csr.lock, flags);
        return ret;
}