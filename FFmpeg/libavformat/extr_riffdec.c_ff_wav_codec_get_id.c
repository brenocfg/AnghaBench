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
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;

/* Variables and functions */
 int AV_CODEC_ID_ADPCM_IMA_WAV ; 
 int AV_CODEC_ID_PCM_F32LE ; 
 int AV_CODEC_ID_PCM_S16LE ; 
 int AV_CODEC_ID_PCM_ZORK ; 
 int ff_codec_get_id (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ff_codec_wav_tags ; 
 int ff_get_pcm_codec_id (int,int,int /*<<< orphan*/ ,int) ; 

enum AVCodecID ff_wav_codec_get_id(unsigned int tag, int bps)
{
    enum AVCodecID id;
    id = ff_codec_get_id(ff_codec_wav_tags, tag);
    if (id <= 0)
        return id;

    if (id == AV_CODEC_ID_PCM_S16LE)
        id = ff_get_pcm_codec_id(bps, 0, 0, ~1);
    else if (id == AV_CODEC_ID_PCM_F32LE)
        id = ff_get_pcm_codec_id(bps, 1, 0,  0);

    if (id == AV_CODEC_ID_ADPCM_IMA_WAV && bps == 8)
        id = AV_CODEC_ID_PCM_ZORK;
    return id;
}