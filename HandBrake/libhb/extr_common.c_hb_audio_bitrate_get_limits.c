#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {int rate; } ;
struct TYPE_7__ {int rate; } ;
struct TYPE_6__ {int rate; } ;
struct TYPE_5__ {int rate; } ;

/* Variables and functions */
#define  HB_ACODEC_AC3 139 
#define  HB_ACODEC_CA_AAC 138 
#define  HB_ACODEC_CA_HAAC 137 
#define  HB_ACODEC_FDK_AAC 136 
#define  HB_ACODEC_FDK_HAAC 135 
#define  HB_ACODEC_FFAAC 134 
#define  HB_ACODEC_FFEAC3 133 
#define  HB_ACODEC_FFFLAC 132 
#define  HB_ACODEC_FFFLAC24 131 
#define  HB_ACODEC_LAME 130 
#define  HB_ACODEC_OPUS 129 
#define  HB_ACODEC_VORBIS 128 
 TYPE_4__* hb_audio_bitrates_first_item ; 
 TYPE_3__* hb_audio_bitrates_last_item ; 
 TYPE_2__* hb_audio_rates_first_item ; 
 TYPE_1__* hb_audio_rates_last_item ; 
 int hb_audio_samplerate_find_closest (int,int) ; 
 int hb_audio_samplerate_get_sr_shift (int) ; 
 int hb_mixdown_get_discrete_channel_count (int) ; 
 int hb_mixdown_get_low_freq_channel_count (int) ; 

void hb_audio_bitrate_get_limits(uint32_t codec, int samplerate, int mixdown,
                                 int *low, int *high)
{
    /*
     * samplerate == 0 means "auto" (same as source) and the UIs know the source
     * samplerate -- except where there isn't a source (audio defaults panel);
     * but we have enough info to return the global bitrate limits for this
     * mixdown, since the first/last samplerate are known to us and non-zero.
     */
    if (samplerate == 0)
    {
        int dummy;
        hb_audio_bitrate_get_limits(codec, hb_audio_rates_first_item->rate, mixdown, low, &dummy);
        hb_audio_bitrate_get_limits(codec, hb_audio_rates_last_item->rate, mixdown, &dummy, high);
        return;
    }

    /* samplerate, sr_shift */
    int sr_shift;
    samplerate = hb_audio_samplerate_find_closest(samplerate, codec);
    sr_shift = hb_audio_samplerate_get_sr_shift(samplerate);

    /* LFE, full-bandwidth channels */
    int lfe_count, nchannels;
    lfe_count = hb_mixdown_get_low_freq_channel_count(mixdown);
    nchannels = hb_mixdown_get_discrete_channel_count(mixdown) - lfe_count;

    switch (codec)
    {
        // Bitrates don't apply to "lossless" audio
        case HB_ACODEC_FFFLAC:
        case HB_ACODEC_FFFLAC24:
            *low = *high = -1;
            return;

        case HB_ACODEC_AC3:
            *low  = 224 * nchannels / 5;
            *high = 640;
            break;

        case HB_ACODEC_FFEAC3:
            *low  = 224 * nchannels  /    5;
            *high = 128 * samplerate / 1000;
            break;

        case HB_ACODEC_CA_AAC:
        {
            switch (samplerate)
            {
                case 8000:
                    *low  = nchannels *  8;
                    *high = nchannels * 24;
                    break;

                case 11025:
                case 12000:
                    *low  = nchannels * 12;
                    *high = nchannels * 32;
                    break;

                case 16000:
                    *low  = nchannels * 12;
                    *high = nchannels * 48;
                    break;

                case 22050:
                case 24000:
                    *low  = nchannels * 16;
                    *high = nchannels * 64;
                    break;

                case 32000:
                    *low  = nchannels * 24;
                    *high = nchannels * 96;
                    break;

                case 44100:
                case 48000:
                default:
                    *low  = nchannels * 32;
                    *high = nchannels * (160 + (96 * (nchannels == 1)));
                    break;
            } break;
        }

        case HB_ACODEC_CA_HAAC:
            *low  = nchannels * (12 + (4 * (samplerate >= 44100)));
            *high = nchannels * 40;
            break;

        case HB_ACODEC_FDK_AAC:
            *low  = nchannels * samplerate * 2 / 3000;
            *high = nchannels * samplerate * 6 / 1000;
            break;

        case HB_ACODEC_FDK_HAAC:
            *low  = (nchannels * (12 + (4 * (samplerate >= 44100))));
            *high = (nchannels - (nchannels > 2)) * (48 +
                                                     (16 *
                                                      (samplerate >= 22050)));
            break;

        case HB_ACODEC_FFAAC:
            *low  = ((nchannels + lfe_count) * 32);
            *high = ((nchannels + lfe_count) *
                     ((192 + (64 * ((samplerate << sr_shift) >= 44100)))
                      >> sr_shift));
            break;

        case HB_ACODEC_LAME:
            *low  =  8 + (24 * (sr_shift < 1));
            *high = 64 + (96 * (sr_shift < 2)) + (160 * (sr_shift < 1));
            break;

        case HB_ACODEC_VORBIS:
            *low  = (nchannels + lfe_count) * (14 +
                                               (8 * (sr_shift < 2)) +
                                               (6 * (sr_shift < 1)));
            *high = (nchannels + lfe_count) * (32 +
                                               ( 54 * (sr_shift < 2)) +
                                               (104 * (sr_shift < 1)) +
                                               ( 50 * (samplerate >= 44100)));
            break;

        case HB_ACODEC_OPUS:
            *low  = (nchannels + lfe_count) * 6;
            *high = (nchannels + lfe_count) * 256;
            break;

        // Bitrates don't apply to passthrough audio, but may apply if we
        // fall back to an encoder when the source can't be passed through.
        default:
            *low  = hb_audio_bitrates_first_item->rate;
            *high = hb_audio_bitrates_last_item ->rate;
            break;
    }

    // sanitize max. bitrate
    if (*high < hb_audio_bitrates_first_item->rate)
        *high = hb_audio_bitrates_first_item->rate;
    if (*high > hb_audio_bitrates_last_item ->rate)
        *high = hb_audio_bitrates_last_item ->rate;
}