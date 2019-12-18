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
struct snd_soc_dai {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set_tdm_slot ) (struct snd_soc_dai*,unsigned int,unsigned int,int,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct snd_soc_dai*,unsigned int,unsigned int,int,int) ; 

int snd_soc_dai_set_tdm_slot(struct snd_soc_dai *dai,
	unsigned int tx_mask, unsigned int rx_mask, int slots, int slot_width)
{
	if (dai->ops && dai->ops->set_tdm_slot)
		return dai->ops->set_tdm_slot(dai, tx_mask, rx_mask,
				slots, slot_width);
	else
		return -EINVAL;
}