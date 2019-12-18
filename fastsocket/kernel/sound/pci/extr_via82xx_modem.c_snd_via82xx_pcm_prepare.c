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
struct viadev {int dummy; } ;
struct via82xx_modem {int dummy; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {struct viadev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFFSET_TYPE ; 
 int /*<<< orphan*/  VIADEV_REG (struct viadev*,int /*<<< orphan*/ ) ; 
 int VIA_REG_TYPE_AUTOSTART ; 
 int VIA_REG_TYPE_INT_EOL ; 
 int VIA_REG_TYPE_INT_FLAG ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 struct via82xx_modem* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_via82xx_channel_reset (struct via82xx_modem*,struct viadev*) ; 
 int /*<<< orphan*/  snd_via82xx_set_table_ptr (struct via82xx_modem*,struct viadev*) ; 

__attribute__((used)) static int snd_via82xx_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct via82xx_modem *chip = snd_pcm_substream_chip(substream);
	struct viadev *viadev = substream->runtime->private_data;

	snd_via82xx_channel_reset(chip, viadev);
	/* this must be set after channel_reset */
	snd_via82xx_set_table_ptr(chip, viadev);
	outb(VIA_REG_TYPE_AUTOSTART|VIA_REG_TYPE_INT_EOL|VIA_REG_TYPE_INT_FLAG,
	     VIADEV_REG(viadev, OFFSET_TYPE));
	return 0;
}