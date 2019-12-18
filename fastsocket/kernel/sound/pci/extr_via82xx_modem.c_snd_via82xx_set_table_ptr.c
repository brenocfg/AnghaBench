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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ addr; } ;
struct viadev {TYPE_1__ table; } ;
struct via82xx_modem {int /*<<< orphan*/  ac97_secondary; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFFSET_TABLE_PTR ; 
 int /*<<< orphan*/  VIADEV_REG (struct viadev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_via82xx_codec_ready (struct via82xx_modem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_via82xx_set_table_ptr(struct via82xx_modem *chip, struct viadev *viadev)
{
	snd_via82xx_codec_ready(chip, chip->ac97_secondary);
	outl((u32)viadev->table.addr, VIADEV_REG(viadev, OFFSET_TABLE_PTR));
	udelay(20);
	snd_via82xx_codec_ready(chip, chip->ac97_secondary);
}