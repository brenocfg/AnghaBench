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
struct ps3flash_private {int dirty; scalar_t__ tag; } ;
struct ps3_storage_device {int /*<<< orphan*/  sbd; } ;

/* Variables and functions */
 struct ps3flash_private* ps3_system_bus_get_drvdata (int /*<<< orphan*/ *) ; 
 int ps3flash_read_write_sectors (struct ps3_storage_device*,scalar_t__,int) ; 

__attribute__((used)) static int ps3flash_writeback(struct ps3_storage_device *dev)
{
	struct ps3flash_private *priv = ps3_system_bus_get_drvdata(&dev->sbd);
	int res;

	if (!priv->dirty || priv->tag < 0)
		return 0;

	res = ps3flash_read_write_sectors(dev, priv->tag, 1);
	if (res)
		return res;

	priv->dirty = false;
	return 0;
}