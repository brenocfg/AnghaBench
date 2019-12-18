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
struct ps3vram_cache {int page_count; TYPE_1__* tags; } ;
struct ps3vram_priv {struct ps3vram_cache cache; } ;
struct ps3_system_bus_device {int /*<<< orphan*/  core; } ;
struct TYPE_2__ {scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct ps3vram_priv* ps3_system_bus_get_drvdata (struct ps3_system_bus_device*) ; 
 int /*<<< orphan*/  ps3vram_cache_evict (struct ps3_system_bus_device*,int) ; 

__attribute__((used)) static void ps3vram_cache_flush(struct ps3_system_bus_device *dev)
{
	struct ps3vram_priv *priv = ps3_system_bus_get_drvdata(dev);
	struct ps3vram_cache *cache = &priv->cache;
	int i;

	dev_dbg(&dev->core, "FLUSH\n");
	for (i = 0; i < cache->page_count; i++) {
		ps3vram_cache_evict(dev, i);
		cache->tags[i].flags = 0;
	}
}