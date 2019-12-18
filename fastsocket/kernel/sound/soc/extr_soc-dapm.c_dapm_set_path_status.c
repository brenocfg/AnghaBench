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
struct soc_mixer_control {unsigned int reg; unsigned int shift; int max; unsigned int invert; } ;
struct soc_enum {int max; unsigned int reg; int shift_l; int mask; int* values; int /*<<< orphan*/ * texts; } ;
struct snd_soc_dapm_widget {int id; int /*<<< orphan*/  codec; TYPE_1__* kcontrols; } ;
struct snd_soc_dapm_path {int connect; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ private_value; } ;

/* Variables and functions */
 int fls (int) ; 
#define  snd_soc_dapm_adc 148 
#define  snd_soc_dapm_aif_in 147 
#define  snd_soc_dapm_aif_out 146 
#define  snd_soc_dapm_dac 145 
#define  snd_soc_dapm_hp 144 
#define  snd_soc_dapm_input 143 
#define  snd_soc_dapm_line 142 
#define  snd_soc_dapm_mic 141 
#define  snd_soc_dapm_micbias 140 
#define  snd_soc_dapm_mixer 139 
#define  snd_soc_dapm_mixer_named_ctl 138 
#define  snd_soc_dapm_mux 137 
#define  snd_soc_dapm_output 136 
#define  snd_soc_dapm_pga 135 
#define  snd_soc_dapm_post 134 
#define  snd_soc_dapm_pre 133 
#define  snd_soc_dapm_spk 132 
#define  snd_soc_dapm_supply 131 
#define  snd_soc_dapm_switch 130 
#define  snd_soc_dapm_value_mux 129 
#define  snd_soc_dapm_vmid 128 
 int snd_soc_read (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dapm_set_path_status(struct snd_soc_dapm_widget *w,
	struct snd_soc_dapm_path *p, int i)
{
	switch (w->id) {
	case snd_soc_dapm_switch:
	case snd_soc_dapm_mixer:
	case snd_soc_dapm_mixer_named_ctl: {
		int val;
		struct soc_mixer_control *mc = (struct soc_mixer_control *)
			w->kcontrols[i].private_value;
		unsigned int reg = mc->reg;
		unsigned int shift = mc->shift;
		int max = mc->max;
		unsigned int mask = (1 << fls(max)) - 1;
		unsigned int invert = mc->invert;

		val = snd_soc_read(w->codec, reg);
		val = (val >> shift) & mask;

		if ((invert && !val) || (!invert && val))
			p->connect = 1;
		else
			p->connect = 0;
	}
	break;
	case snd_soc_dapm_mux: {
		struct soc_enum *e = (struct soc_enum *)w->kcontrols[i].private_value;
		int val, item, bitmask;

		for (bitmask = 1; bitmask < e->max; bitmask <<= 1)
		;
		val = snd_soc_read(w->codec, e->reg);
		item = (val >> e->shift_l) & (bitmask - 1);

		p->connect = 0;
		for (i = 0; i < e->max; i++) {
			if (!(strcmp(p->name, e->texts[i])) && item == i)
				p->connect = 1;
		}
	}
	break;
	case snd_soc_dapm_value_mux: {
		struct soc_enum *e = (struct soc_enum *)
			w->kcontrols[i].private_value;
		int val, item;

		val = snd_soc_read(w->codec, e->reg);
		val = (val >> e->shift_l) & e->mask;
		for (item = 0; item < e->max; item++) {
			if (val == e->values[item])
				break;
		}

		p->connect = 0;
		for (i = 0; i < e->max; i++) {
			if (!(strcmp(p->name, e->texts[i])) && item == i)
				p->connect = 1;
		}
	}
	break;
	/* does not effect routing - always connected */
	case snd_soc_dapm_pga:
	case snd_soc_dapm_output:
	case snd_soc_dapm_adc:
	case snd_soc_dapm_input:
	case snd_soc_dapm_dac:
	case snd_soc_dapm_micbias:
	case snd_soc_dapm_vmid:
	case snd_soc_dapm_supply:
	case snd_soc_dapm_aif_in:
	case snd_soc_dapm_aif_out:
		p->connect = 1;
	break;
	/* does effect routing - dynamically connected */
	case snd_soc_dapm_hp:
	case snd_soc_dapm_mic:
	case snd_soc_dapm_spk:
	case snd_soc_dapm_line:
	case snd_soc_dapm_pre:
	case snd_soc_dapm_post:
		p->connect = 0;
	break;
	}
}