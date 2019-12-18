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
struct TYPE_2__ {int hz; unsigned int hda_fmt; } ;

/* Variables and functions */
 unsigned short AC_DIG1_NONAUDIO ; 
 unsigned int AC_FMT_BITS_16 ; 
 unsigned int AC_FMT_BITS_20 ; 
 unsigned int AC_FMT_BITS_24 ; 
 unsigned int AC_FMT_BITS_32 ; 
 unsigned int AC_FMT_BITS_8 ; 
 unsigned int AC_FMT_TYPE_NON_PCM ; 
 unsigned int SNDRV_PCM_FORMAT_FLOAT_LE ; 
 TYPE_1__* rate_bits ; 
 int snd_pcm_format_width (unsigned int) ; 
 int /*<<< orphan*/  snd_printdd (char*,int) ; 

unsigned int snd_hda_calc_stream_format(unsigned int rate,
					unsigned int channels,
					unsigned int format,
					unsigned int maxbps,
					unsigned short spdif_ctls)
{
	int i;
	unsigned int val = 0;

	for (i = 0; rate_bits[i].hz; i++)
		if (rate_bits[i].hz == rate) {
			val = rate_bits[i].hda_fmt;
			break;
		}
	if (!rate_bits[i].hz) {
		snd_printdd("invalid rate %d\n", rate);
		return 0;
	}

	if (channels == 0 || channels > 8) {
		snd_printdd("invalid channels %d\n", channels);
		return 0;
	}
	val |= channels - 1;

	switch (snd_pcm_format_width(format)) {
	case 8:
		val |= AC_FMT_BITS_8;
		break;
	case 16:
		val |= AC_FMT_BITS_16;
		break;
	case 20:
	case 24:
	case 32:
		if (maxbps >= 32 || format == SNDRV_PCM_FORMAT_FLOAT_LE)
			val |= AC_FMT_BITS_32;
		else if (maxbps >= 24)
			val |= AC_FMT_BITS_24;
		else
			val |= AC_FMT_BITS_20;
		break;
	default:
		snd_printdd("invalid format width %d\n",
			    snd_pcm_format_width(format));
		return 0;
	}

	if (spdif_ctls & AC_DIG1_NONAUDIO)
		val |= AC_FMT_TYPE_NON_PCM;

	return val;
}