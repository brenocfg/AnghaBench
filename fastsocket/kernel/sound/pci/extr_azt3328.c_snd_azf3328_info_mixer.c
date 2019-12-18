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
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_3__ {int max; scalar_t__ min; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_info {TYPE_2__ value; scalar_t__ count; int /*<<< orphan*/  type; } ;
struct azf3328_mixer_reg {int mask; scalar_t__ stereo; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 
 int /*<<< orphan*/  snd_azf3328_dbgcallenter () ; 
 int /*<<< orphan*/  snd_azf3328_dbgcallleave () ; 
 int /*<<< orphan*/  snd_azf3328_mixer_reg_decode (struct azf3328_mixer_reg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snd_azf3328_info_mixer(struct snd_kcontrol *kcontrol,
		       struct snd_ctl_elem_info *uinfo)
{
	struct azf3328_mixer_reg reg;

	snd_azf3328_dbgcallenter();
	snd_azf3328_mixer_reg_decode(&reg, kcontrol->private_value);
	uinfo->type = reg.mask == 1 ?
		SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = reg.stereo + 1;
	uinfo->value.integer.min = 0;
	uinfo->value.integer.max = reg.mask;
	snd_azf3328_dbgcallleave();
	return 0;
}