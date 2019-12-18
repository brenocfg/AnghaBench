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
typedef  int /*<<< orphan*/  u32 ;
struct piix_host_priv {int /*<<< orphan*/  sidpr_lock; scalar_t__ sidpr; } ;
struct ata_link {TYPE_2__* ap; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {struct piix_host_priv* private_data; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ PIIX_SIDPR_DATA ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  piix_sidpr_sel (struct ata_link*,unsigned int) ; 
 int /*<<< orphan*/  piix_sidx_map ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int piix_sidpr_scr_write(struct ata_link *link,
				unsigned int reg, u32 val)
{
	struct piix_host_priv *hpriv = link->ap->host->private_data;
	unsigned long flags;

	if (reg >= ARRAY_SIZE(piix_sidx_map))
		return -EINVAL;

	spin_lock_irqsave(&hpriv->sidpr_lock, flags);
	piix_sidpr_sel(link, reg);
	iowrite32(val, hpriv->sidpr + PIIX_SIDPR_DATA);
	spin_unlock_irqrestore(&hpriv->sidpr_lock, flags);
	return 0;
}