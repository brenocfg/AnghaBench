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
struct TYPE_4__ {int /*<<< orphan*/  area; } ;
struct TYPE_3__ {int format; } ;
struct snd_harmony {TYPE_2__ sdma; TYPE_1__ st; } ;

/* Variables and functions */
 int HARMONY_DF_16BIT_LINEAR ; 
 int HARMONY_DF_8BIT_ALAW ; 
 int HARMONY_DF_8BIT_ULAW ; 
 int SILENCE_BUFSZ ; 
#define  SNDRV_PCM_FORMAT_A_LAW 130 
#define  SNDRV_PCM_FORMAT_MU_LAW 129 
#define  SNDRV_PCM_FORMAT_S16_BE 128 
 int snd_pcm_format_physical_width (int) ; 
 int /*<<< orphan*/  snd_pcm_format_set_silence (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
snd_harmony_set_data_format(struct snd_harmony *h, int fmt, int force)
{
	int o = h->st.format;
	int n;

	switch(fmt) {
	case SNDRV_PCM_FORMAT_S16_BE:
		n = HARMONY_DF_16BIT_LINEAR;
		break;
	case SNDRV_PCM_FORMAT_A_LAW:
		n = HARMONY_DF_8BIT_ALAW;
		break;
	case SNDRV_PCM_FORMAT_MU_LAW:
		n = HARMONY_DF_8BIT_ULAW;
		break;
	default:
		n = HARMONY_DF_16BIT_LINEAR;
		break;
	}

	if (force || o != n) {
		snd_pcm_format_set_silence(fmt, h->sdma.area, SILENCE_BUFSZ / 
					   (snd_pcm_format_physical_width(fmt)
					    / 8));
	}

	return n;
}