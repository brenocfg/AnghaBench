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
struct TYPE_3__ {unsigned int items; unsigned int item; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_info {int count; TYPE_2__ value; int /*<<< orphan*/  type; } ;
struct azf3328_mixer_reg {scalar_t__ reg; unsigned int enum_c; int lchan_shift; } ;

/* Variables and functions */
 scalar_t__ IDX_MIXER_ADVCTL2 ; 
 scalar_t__ IDX_MIXER_REC_SELECT ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 int /*<<< orphan*/  snd_azf3328_mixer_reg_decode (struct azf3328_mixer_reg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const* const) ; 

__attribute__((used)) static int
snd_azf3328_info_mixer_enum(struct snd_kcontrol *kcontrol,
			    struct snd_ctl_elem_info *uinfo)
{
	static const char * const texts1[] = {
		"Mic1", "Mic2"
	};
	static const char * const texts2[] = {
		"Mix", "Mic"
	};
	static const char * const texts3[] = {
		"Mic", "CD", "Video", "Aux",
		"Line", "Mix", "Mix Mono", "Phone"
        };
	static const char * const texts4[] = {
		"pre 3D", "post 3D"
        };
	struct azf3328_mixer_reg reg;
	const char * const *p = NULL;

	snd_azf3328_mixer_reg_decode(&reg, kcontrol->private_value);
        uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
        uinfo->count = (reg.reg == IDX_MIXER_REC_SELECT) ? 2 : 1;
        uinfo->value.enumerated.items = reg.enum_c;
        if (uinfo->value.enumerated.item > reg.enum_c - 1U)
                uinfo->value.enumerated.item = reg.enum_c - 1U;
	if (reg.reg == IDX_MIXER_ADVCTL2) {
		switch(reg.lchan_shift) {
		case 8: /* modem out sel */
			p = texts1;
			break;
		case 9: /* mono sel source */
			p = texts2;
			break;
		case 15: /* PCM Out Path */
			p = texts4;
			break;
		}
	} else
	if (reg.reg == IDX_MIXER_REC_SELECT)
		p = texts3;

	strcpy(uinfo->value.enumerated.name, p[uinfo->value.enumerated.item]);
        return 0;
}