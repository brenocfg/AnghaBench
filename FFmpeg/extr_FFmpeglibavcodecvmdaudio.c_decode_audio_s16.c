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
typedef  int uint8_t ;
typedef  int int16_t ;

/* Variables and functions */
 scalar_t__ AV_RL16 (int const*) ; 
 int av_clip_int16 (int) ; 
 scalar_t__* vmdaudio_table ; 

__attribute__((used)) static void decode_audio_s16(int16_t *out, const uint8_t *buf, int buf_size,
                             int channels)
{
    int ch;
    const uint8_t *buf_end = buf + buf_size;
    int predictor[2];
    int st = channels - 1;

    /* decode initial raw sample */
    for (ch = 0; ch < channels; ch++) {
        predictor[ch] = (int16_t)AV_RL16(buf);
        buf += 2;
        *out++ = predictor[ch];
    }

    /* decode DPCM samples */
    ch = 0;
    while (buf < buf_end) {
        uint8_t b = *buf++;
        if (b & 0x80)
            predictor[ch] -= vmdaudio_table[b & 0x7F];
        else
            predictor[ch] += vmdaudio_table[b];
        predictor[ch] = av_clip_int16(predictor[ch]);
        *out++ = predictor[ch];
        ch ^= st;
    }
}