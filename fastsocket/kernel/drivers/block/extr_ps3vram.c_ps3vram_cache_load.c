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
struct ps3vram_cache {int page_size; TYPE_1__* tags; } ;
struct ps3vram_priv {struct ps3vram_cache cache; } ;
struct ps3_system_bus_device {int /*<<< orphan*/  core; } ;
struct TYPE_2__ {unsigned int address; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ CACHE_OFFSET ; 
 int /*<<< orphan*/  CACHE_PAGE_PRESENT ; 
 int DMA_PAGE_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,int,int) ; 
 struct ps3vram_priv* ps3_system_bus_get_drvdata (struct ps3_system_bus_device*) ; 
 scalar_t__ ps3vram_download (struct ps3_system_bus_device*,unsigned int,scalar_t__,int,int) ; 

__attribute__((used)) static void ps3vram_cache_load(struct ps3_system_bus_device *dev, int entry,
			       unsigned int address)
{
	struct ps3vram_priv *priv = ps3_system_bus_get_drvdata(dev);
	struct ps3vram_cache *cache = &priv->cache;

	dev_dbg(&dev->core, "Fetching %d: 0x%08x\n", entry, address);
	if (ps3vram_download(dev, address,
			     CACHE_OFFSET + entry * cache->page_size,
			     DMA_PAGE_SIZE,
			     cache->page_size / DMA_PAGE_SIZE) < 0) {
		dev_err(&dev->core,
			"Failed to download from 0x%x to 0x%x size 0x%x\n",
			address, entry * cache->page_size, cache->page_size);
	}

	cache->tags[entry].address = address;
	cache->tags[entry].flags |= CACHE_PAGE_PRESENT;
}