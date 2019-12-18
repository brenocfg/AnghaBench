#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int* audio_min_samples; int difseg_size; int height; int n_difchan; int** audio_shuffle; int audio_stride; } ;
typedef  TYPE_1__ AVDVProfile ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int dv_audio_12to16 (int) ; 
 int /*<<< orphan*/  dv_audio_frequency ; 
 int /*<<< orphan*/  dv_audio_source ; 
 int* dv_extract_pack (int const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dv_extract_audio(const uint8_t *frame, uint8_t **ppcm,
                            const AVDVProfile *sys)
{
    int size, chan, i, j, d, of, smpls, freq, quant, half_ch;
    uint16_t lc, rc;
    const uint8_t *as_pack;
    uint8_t *pcm, ipcm;

    as_pack = dv_extract_pack(frame, dv_audio_source);
    if (!as_pack)    /* No audio ? */
        return 0;

    smpls = as_pack[1]      & 0x3f; /* samples in this frame - min. samples */
    freq  = as_pack[4] >> 3 & 0x07; /* 0 - 48kHz, 1 - 44,1kHz, 2 - 32kHz */
    quant = as_pack[4]      & 0x07; /* 0 - 16-bit linear, 1 - 12-bit nonlinear */

    if (quant > 1)
        return -1;  /* unsupported quantization */

    if (freq >= FF_ARRAY_ELEMS(dv_audio_frequency))
        return AVERROR_INVALIDDATA;

    size    = (sys->audio_min_samples[freq] + smpls) * 4; /* 2ch, 2bytes */
    half_ch = sys->difseg_size / 2;

    /* We work with 720p frames split in half, thus even frames have
     * channels 0,1 and odd 2,3. */
    ipcm = (sys->height == 720 && !(frame[1] & 0x0C)) ? 2 : 0;

    if (ipcm + sys->n_difchan > (quant == 1 ? 2 : 4)) {
        av_log(NULL, AV_LOG_ERROR, "too many dv pcm frames\n");
        return AVERROR_INVALIDDATA;
    }

    /* for each DIF channel */
    for (chan = 0; chan < sys->n_difchan; chan++) {
        av_assert0(ipcm<4);
        pcm = ppcm[ipcm++];
        if (!pcm)
            break;

        /* for each DIF segment */
        for (i = 0; i < sys->difseg_size; i++) {
            frame += 6 * 80; /* skip DIF segment header */
            if (quant == 1 && i == half_ch) {
                /* next stereo channel (12-bit mode only) */
                av_assert0(ipcm<4);
                pcm = ppcm[ipcm++];
                if (!pcm)
                    break;
            }

            /* for each AV sequence */
            for (j = 0; j < 9; j++) {
                for (d = 8; d < 80; d += 2) {
                    if (quant == 0) {  /* 16-bit quantization */
                        of = sys->audio_shuffle[i][j] +
                             (d - 8) / 2 * sys->audio_stride;
                        if (of * 2 >= size)
                            continue;

                        /* FIXME: maybe we have to admit that DV is a
                         * big-endian PCM */
                        pcm[of * 2]     = frame[d + 1];
                        pcm[of * 2 + 1] = frame[d];

                        if (pcm[of * 2 + 1] == 0x80 && pcm[of * 2] == 0x00)
                            pcm[of * 2 + 1] = 0;
                    } else {           /* 12-bit quantization */
                        lc = ((uint16_t)frame[d]     << 4) |
                             ((uint16_t)frame[d + 2] >> 4);
                        rc = ((uint16_t)frame[d + 1] << 4) |
                             ((uint16_t)frame[d + 2] & 0x0f);
                        lc = (lc == 0x800 ? 0 : dv_audio_12to16(lc));
                        rc = (rc == 0x800 ? 0 : dv_audio_12to16(rc));

                        of = sys->audio_shuffle[i % half_ch][j] +
                             (d - 8) / 3 * sys->audio_stride;
                        if (of * 2 >= size)
                            continue;

                        /* FIXME: maybe we have to admit that DV is a
                         * big-endian PCM */
                        pcm[of * 2]     = lc & 0xff;
                        pcm[of * 2 + 1] = lc >> 8;
                        of = sys->audio_shuffle[i % half_ch + half_ch][j] +
                             (d - 8) / 3 * sys->audio_stride;
                        /* FIXME: maybe we have to admit that DV is a
                         * big-endian PCM */
                        pcm[of * 2]     = rc & 0xff;
                        pcm[of * 2 + 1] = rc >> 8;
                        ++d;
                    }
                }

                frame += 16 * 80; /* 15 Video DIFs + 1 Audio DIF */
            }
        }
    }

    return size;
}