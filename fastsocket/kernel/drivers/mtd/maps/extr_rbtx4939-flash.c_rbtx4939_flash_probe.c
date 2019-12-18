#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_13__ {unsigned long size; int /*<<< orphan*/  virt; int /*<<< orphan*/  phys; int /*<<< orphan*/  bankwidth; int /*<<< orphan*/  name; } ;
struct rbtx4939_flash_info {int nr_parts; TYPE_3__* mtd; int /*<<< orphan*/  parts; TYPE_1__ map; } ;
struct rbtx4939_flash_data {int nr_parts; int /*<<< orphan*/  parts; int /*<<< orphan*/  (* map_init ) (TYPE_1__*) ;int /*<<< orphan*/  width; } ;
struct TYPE_15__ {struct rbtx4939_flash_data* platform_data; } ;
struct platform_device {TYPE_6__ dev; } ;
struct TYPE_14__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  add_mtd_device (TYPE_3__*) ; 
 int /*<<< orphan*/  add_mtd_partitions (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_6__*) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_6__*,int /*<<< orphan*/ ,unsigned long) ; 
 struct rbtx4939_flash_info* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_mem_region (TYPE_6__*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_3__* do_map_probe (char const*,TYPE_1__*) ; 
 int parse_mtd_partitions (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  part_probe_types ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rbtx4939_flash_info*) ; 
 int /*<<< orphan*/  pr_notice (char*,...) ; 
 int /*<<< orphan*/  rbtx4939_flash_remove (struct platform_device*) ; 
 unsigned long resource_size (struct resource*) ; 
 char** rom_probe_types ; 
 int /*<<< orphan*/  simple_map_init (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static int rbtx4939_flash_probe(struct platform_device *dev)
{
	struct rbtx4939_flash_data *pdata;
	struct rbtx4939_flash_info *info;
	struct resource *res;
	const char **probe_type;
	int err = 0;
	unsigned long size;

	pdata = dev->dev.platform_data;
	if (!pdata)
		return -ENODEV;

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;
	info = devm_kzalloc(&dev->dev, sizeof(struct rbtx4939_flash_info),
			    GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	platform_set_drvdata(dev, info);

	size = resource_size(res);
	pr_notice("rbtx4939 platform flash device: %pR\n", res);

	if (!devm_request_mem_region(&dev->dev, res->start, size,
				     dev_name(&dev->dev)))
		return -EBUSY;

	info->map.name = dev_name(&dev->dev);
	info->map.phys = res->start;
	info->map.size = size;
	info->map.bankwidth = pdata->width;

	info->map.virt = devm_ioremap(&dev->dev, info->map.phys, size);
	if (!info->map.virt)
		return -EBUSY;

	if (pdata->map_init)
		(*pdata->map_init)(&info->map);
	else
		simple_map_init(&info->map);

	probe_type = rom_probe_types;
	for (; !info->mtd && *probe_type; probe_type++)
		info->mtd = do_map_probe(*probe_type, &info->map);
	if (!info->mtd) {
		dev_err(&dev->dev, "map_probe failed\n");
		err = -ENXIO;
		goto err_out;
	}
	info->mtd->owner = THIS_MODULE;
	if (err)
		goto err_out;

#ifdef CONFIG_MTD_PARTITIONS
	err = parse_mtd_partitions(info->mtd, part_probe_types,
				&info->parts, 0);
	if (err > 0) {
		add_mtd_partitions(info->mtd, info->parts, err);
		info->nr_parts = err;
		return 0;
	}

	if (pdata->nr_parts) {
		pr_notice("Using rbtx4939 partition information\n");
		add_mtd_partitions(info->mtd, pdata->parts, pdata->nr_parts);
		return 0;
	}
#endif

	add_mtd_device(info->mtd);
	return 0;

err_out:
	rbtx4939_flash_remove(dev);
	return err;
}