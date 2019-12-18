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
typedef  union sil24_cmd_block {int dummy; } sil24_cmd_block ;
struct sil24_port_priv {int /*<<< orphan*/  cmd_block_dma; union sil24_cmd_block* cmd_block; } ;
struct device {int dummy; } ;
struct ata_port {struct sil24_port_priv* private_data; TYPE_1__* host; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SIL24_HOST_BAR ; 
 int SIL24_MAX_CMDS ; 
 int /*<<< orphan*/  SIL24_PORT_BAR ; 
 int /*<<< orphan*/  ata_port_pbar_desc (struct ata_port*,int /*<<< orphan*/ ,int,char*) ; 
 struct sil24_port_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 union sil24_cmd_block* dmam_alloc_coherent (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union sil24_cmd_block*,int /*<<< orphan*/ ,size_t) ; 
 int sil24_port_offset (struct ata_port*) ; 

__attribute__((used)) static int sil24_port_start(struct ata_port *ap)
{
	struct device *dev = ap->host->dev;
	struct sil24_port_priv *pp;
	union sil24_cmd_block *cb;
	size_t cb_size = sizeof(*cb) * SIL24_MAX_CMDS;
	dma_addr_t cb_dma;

	pp = devm_kzalloc(dev, sizeof(*pp), GFP_KERNEL);
	if (!pp)
		return -ENOMEM;

	cb = dmam_alloc_coherent(dev, cb_size, &cb_dma, GFP_KERNEL);
	if (!cb)
		return -ENOMEM;
	memset(cb, 0, cb_size);

	pp->cmd_block = cb;
	pp->cmd_block_dma = cb_dma;

	ap->private_data = pp;

	ata_port_pbar_desc(ap, SIL24_HOST_BAR, -1, "host");
	ata_port_pbar_desc(ap, SIL24_PORT_BAR, sil24_port_offset(ap), "port");

	return 0;
}