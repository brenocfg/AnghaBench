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
struct src_node_conf_t {unsigned int pitch; int mix_msr; int imp_msr; int msr; int vo; } ;
struct ct_atc_pcm {TYPE_2__* substream; } ;
struct ct_atc {int rsr; int msr; } ;
struct TYPE_4__ {TYPE_1__* runtime; } ;
struct TYPE_3__ {int channels; int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 void* atc_get_pitch (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_src_node_conf(struct ct_atc *atc, struct ct_atc_pcm *apcm,
				struct src_node_conf_t *conf, int *n_srcc)
{
	unsigned int pitch;

	/* get pitch and convert to fixed-point 8.24 format. */
	pitch = atc_get_pitch((atc->rsr * atc->msr),
				apcm->substream->runtime->rate);
	*n_srcc = 0;

	if (1 == atc->msr) {
		*n_srcc = apcm->substream->runtime->channels;
		conf[0].pitch = pitch;
		conf[0].mix_msr = conf[0].imp_msr = conf[0].msr = 1;
		conf[0].vo = 1;
	} else if (2 == atc->msr) {
		if (0x8000000 < pitch) {
			/* Need two-stage SRCs, SRCIMPs and
			 * AMIXERs for converting format */
			conf[0].pitch = (atc->msr << 24);
			conf[0].msr = conf[0].mix_msr = 1;
			conf[0].imp_msr = atc->msr;
			conf[0].vo = 0;
			conf[1].pitch = atc_get_pitch(atc->rsr,
					apcm->substream->runtime->rate);
			conf[1].msr = conf[1].mix_msr = conf[1].imp_msr = 1;
			conf[1].vo = 1;
			*n_srcc = apcm->substream->runtime->channels * 2;
		} else if (0x1000000 < pitch) {
			/* Need one-stage SRCs, SRCIMPs and
			 * AMIXERs for converting format */
			conf[0].pitch = pitch;
			conf[0].msr = conf[0].mix_msr
				    = conf[0].imp_msr = atc->msr;
			conf[0].vo = 1;
			*n_srcc = apcm->substream->runtime->channels;
		}
	}
}