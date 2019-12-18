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
struct ps3vram_cache {int page_size; int page_count; int /*<<< orphan*/  miss; TYPE_1__* tags; int /*<<< orphan*/  hit; } ;
struct ps3vram_priv {struct ps3vram_cache cache; } ;
struct ps3_system_bus_device {int /*<<< orphan*/  core; } ;
typedef  int loff_t ;
struct TYPE_2__ {int flags; unsigned int address; } ;

/* Variables and functions */
 int CACHE_PAGE_PRESENT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int jiffies ; 
 struct ps3vram_priv* ps3_system_bus_get_drvdata (struct ps3_system_bus_device*) ; 
 int /*<<< orphan*/  ps3vram_cache_evict (struct ps3_system_bus_device*,int) ; 
 int /*<<< orphan*/  ps3vram_cache_load (struct ps3_system_bus_device*,int,unsigned int) ; 

__attribute__((used)) static unsigned int ps3vram_cache_match(struct ps3_system_bus_device *dev,
					loff_t address)
{
	struct ps3vram_priv *priv = ps3_system_bus_get_drvdata(dev);
	struct ps3vram_cache *cache = &priv->cache;
	unsigned int base;
	unsigned int offset;
	int i;
	static int counter;

	offset = (unsigned int) (address & (cache->page_size - 1));
	base = (unsigned int) (address - offset);

	/* fully associative check */
	for (i = 0; i < cache->page_count; i++) {
		if ((cache->tags[i].flags & CACHE_PAGE_PRESENT) &&
		    cache->tags[i].address == base) {
			cache->hit++;
			dev_dbg(&dev->core, "Found entry %d: 0x%08x\n", i,
				cache->tags[i].address);
			return i;
		}
	}

	/* choose a random entry */
	i = (jiffies + (counter++)) % cache->page_count;
	dev_dbg(&dev->core, "Using entry %d\n", i);

	ps3vram_cache_evict(dev, i);
	ps3vram_cache_load(dev, i, base);

	cache->miss++;
	return i;
}