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
struct snd_kcontrol {int private_value; } ;
struct snd_ac97 {int ext_id; int /*<<< orphan*/  page_mutex; } ;

/* Variables and functions */
 int AC97_EI_REV_23 ; 
 int AC97_EI_REV_MASK ; 
 int /*<<< orphan*/  AC97_INT_PAGING ; 
 int AC97_PAGE_MASK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int snd_ac97_read (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static int snd_ac97_page_save(struct snd_ac97 *ac97, int reg, struct snd_kcontrol *kcontrol)
{
	int page_save = -1;
	if ((kcontrol->private_value & (1<<25)) &&
	    (ac97->ext_id & AC97_EI_REV_MASK) >= AC97_EI_REV_23 &&
	    (reg >= 0x60 && reg < 0x70)) {
		unsigned short page = (kcontrol->private_value >> 26) & 0x0f;
		mutex_lock(&ac97->page_mutex); /* lock paging */
		page_save = snd_ac97_read(ac97, AC97_INT_PAGING) & AC97_PAGE_MASK;
		snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, page);
	}
	return page_save;
}