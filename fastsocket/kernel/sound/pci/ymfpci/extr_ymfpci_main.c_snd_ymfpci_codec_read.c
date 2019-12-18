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
typedef  int u16 ;
struct snd_ymfpci {scalar_t__ device_id; int rev; } ;
struct snd_ac97 {struct snd_ymfpci* private_data; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_YAMAHA_744 ; 
 int /*<<< orphan*/  YDSXGR_AC97CMDADR ; 
 int /*<<< orphan*/  YDSXGR_PRISTATUSDATA ; 
 int YDSXG_AC97READCMD ; 
 scalar_t__ snd_ymfpci_codec_ready (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int snd_ymfpci_readw (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_writew (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u16 snd_ymfpci_codec_read(struct snd_ac97 *ac97, u16 reg)
{
	struct snd_ymfpci *chip = ac97->private_data;

	if (snd_ymfpci_codec_ready(chip, 0))
		return ~0;
	snd_ymfpci_writew(chip, YDSXGR_AC97CMDADR, YDSXG_AC97READCMD | reg);
	if (snd_ymfpci_codec_ready(chip, 0))
		return ~0;
	if (chip->device_id == PCI_DEVICE_ID_YAMAHA_744 && chip->rev < 2) {
		int i;
		for (i = 0; i < 600; i++)
			snd_ymfpci_readw(chip, YDSXGR_PRISTATUSDATA);
	}
	return snd_ymfpci_readw(chip, YDSXGR_PRISTATUSDATA);
}