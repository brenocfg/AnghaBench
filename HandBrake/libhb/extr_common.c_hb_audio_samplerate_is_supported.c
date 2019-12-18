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
typedef  int uint32_t ;

/* Variables and functions */
#define  HB_ACODEC_AC3 132 
#define  HB_ACODEC_CA_HAAC 131 
#define  HB_ACODEC_FDK_HAAC 130 
#define  HB_ACODEC_FFEAC3 129 
#define  HB_ACODEC_OPUS 128 

int hb_audio_samplerate_is_supported(int samplerate, uint32_t codec)
{
    switch (codec)
    {
        case HB_ACODEC_AC3:
        case HB_ACODEC_FFEAC3:
        case HB_ACODEC_CA_HAAC:
            // ca_haac can't do samplerates < 32 kHz
            // libav's E-AC-3 encoder can't do samplerates < 32 kHz
            // AC-3 < 32 kHz suffers from poor hardware compatibility
            if (samplerate < 32000)
                return 0;
            else
                return 1;
        case HB_ACODEC_FDK_HAAC:
            // fdk_haac can't do samplerates < 16 kHz
            if (samplerate < 16000)
                return 0;
             else
                return 1;
        case HB_ACODEC_OPUS:
            switch (samplerate)
            {
                // Opus only supports samplerates 8kHz, 12kHz, 16kHz,
                // 24kHz, 48kHz
                case 8000:
                case 12000:
                case 16000:
                case 24000:
                case 48000:
                    return 1;
                default:
                    return 0;
            }
        default:
            return 1;
    }
}