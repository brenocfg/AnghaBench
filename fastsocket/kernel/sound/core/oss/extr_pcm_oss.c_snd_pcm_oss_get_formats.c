#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {int /*<<< orphan*/  mmap_count; } ;
struct snd_pcm_oss_file {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_mask {int dummy; } ;
struct TYPE_4__ {int direct; } ;
struct TYPE_5__ {TYPE_1__ setup; } ;
struct TYPE_6__ {TYPE_2__ oss; } ;

/* Variables and functions */
 int AFMT_MU_LAW ; 
 int AFMT_S16_BE ; 
 int AFMT_S16_LE ; 
 int AFMT_S24_BE ; 
 int AFMT_S24_LE ; 
 int AFMT_S24_PACKED ; 
 int AFMT_S32_BE ; 
 int AFMT_S32_LE ; 
 int AFMT_S8 ; 
 int AFMT_U16_BE ; 
 int AFMT_U16_LE ; 
 int AFMT_U8 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 int /*<<< orphan*/  _snd_pcm_hw_params_any (struct snd_pcm_hw_params*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct snd_mask* hw_param_mask (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_pcm_hw_params*) ; 
 struct snd_pcm_hw_params* kmalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_3__* oss_substream (struct snd_pcm_substream*) ; 
 scalar_t__ snd_mask_test (struct snd_mask*,int) ; 
 int snd_pcm_hw_refine (struct snd_pcm_substream*,struct snd_pcm_hw_params*) ; 
 int snd_pcm_oss_format_to (int) ; 
 int snd_pcm_oss_get_active_substream (struct snd_pcm_oss_file*,struct snd_pcm_substream**) ; 

__attribute__((used)) static int snd_pcm_oss_get_formats(struct snd_pcm_oss_file *pcm_oss_file)
{
	struct snd_pcm_substream *substream;
	int err;
	int direct;
	struct snd_pcm_hw_params *params;
	unsigned int formats = 0;
	struct snd_mask format_mask;
	int fmt;

	if ((err = snd_pcm_oss_get_active_substream(pcm_oss_file, &substream)) < 0)
		return err;
	if (atomic_read(&substream->mmap_count))
		direct = 1;
	else
		direct = oss_substream(substream)->oss.setup.direct;
	if (!direct)
		return AFMT_MU_LAW | AFMT_U8 |
		       AFMT_S16_LE | AFMT_S16_BE |
		       AFMT_S8 | AFMT_U16_LE |
		       AFMT_U16_BE |
			AFMT_S32_LE | AFMT_S32_BE |
			AFMT_S24_LE | AFMT_S24_BE |
			AFMT_S24_PACKED;
	params = kmalloc(sizeof(*params), GFP_KERNEL);
	if (!params)
		return -ENOMEM;
	_snd_pcm_hw_params_any(params);
	err = snd_pcm_hw_refine(substream, params);
	format_mask = *hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT); 
	kfree(params);
	if (err < 0)
		return err;
	for (fmt = 0; fmt < 32; ++fmt) {
		if (snd_mask_test(&format_mask, fmt)) {
			int f = snd_pcm_oss_format_to(fmt);
			if (f >= 0)
				formats |= f;
		}
	}
	return formats;
}