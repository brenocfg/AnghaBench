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
struct ata_link {TYPE_2__* ap; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* scr_write ) (struct ata_link*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ ata_is_host_link (struct ata_link*) ; 
 int sata_pmp_scr_write (struct ata_link*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sata_scr_valid (struct ata_link*) ; 
 int stub1 (struct ata_link*,int,int /*<<< orphan*/ ) ; 

int sata_scr_write(struct ata_link *link, int reg, u32 val)
{
	if (ata_is_host_link(link)) {
		if (sata_scr_valid(link))
			return link->ap->ops->scr_write(link, reg, val);
		return -EOPNOTSUPP;
	}

	return sata_pmp_scr_write(link, reg, val);
}