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
struct TYPE_3__ {int sample_rate; scalar_t__ codec_id; } ;
typedef  TYPE_1__ AVCodecParameters ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_H264 ; 
 scalar_t__ AV_CODEC_ID_MP2 ; 
 scalar_t__ AV_CODEC_ID_MP3 ; 
 scalar_t__ AV_CODEC_ID_MPEG1VIDEO ; 
 scalar_t__ AV_CODEC_ID_MPEG2VIDEO ; 
 scalar_t__ AV_CODEC_ID_MPEG4 ; 
 int /*<<< orphan*/  AV_WB24 (int*,int) ; 
 int /*<<< orphan*/  AV_WB32 (int*,unsigned int) ; 
 int*** avpriv_mpa_bitrate_tab ; 
 int* avpriv_mpa_freq_tab ; 

__attribute__((used)) static int find_expected_header(AVCodecParameters *p, int size, int key_frame,
                                uint8_t out[64])
{
    int sample_rate = p->sample_rate;

    if (size > 4096)
        return 0;

    AV_WB24(out, 1);

    if (p->codec_id == AV_CODEC_ID_MPEG4) {
        if (key_frame) {
            return 3;
        } else {
            out[3] = 0xB6;
            return 4;
        }
    } else if (p->codec_id == AV_CODEC_ID_MPEG1VIDEO ||
               p->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
        return 3;
    } else if (p->codec_id == AV_CODEC_ID_H264) {
        return 3;
    } else if (p->codec_id == AV_CODEC_ID_MP3 ||
               p->codec_id == AV_CODEC_ID_MP2) {
        int lsf, mpeg25, sample_rate_index, bitrate_index, frame_size;
        int layer           = p->codec_id == AV_CODEC_ID_MP3 ? 3 : 2;
        unsigned int header = 0xFFF00000;

        lsf           = sample_rate < (24000 + 32000) / 2;
        mpeg25        = sample_rate < (12000 + 16000) / 2;
        sample_rate <<= lsf + mpeg25;
        if      (sample_rate < (32000 + 44100) / 2) sample_rate_index = 2;
        else if (sample_rate < (44100 + 48000) / 2) sample_rate_index = 0;
        else                                        sample_rate_index = 1;

        sample_rate = avpriv_mpa_freq_tab[sample_rate_index] >> (lsf + mpeg25);

        for (bitrate_index = 2; bitrate_index < 30; bitrate_index++) {
            frame_size =
                avpriv_mpa_bitrate_tab[lsf][layer - 1][bitrate_index >> 1];
            frame_size = (frame_size * 144000) / (sample_rate << lsf) +
                (bitrate_index & 1);

            if (frame_size == size)
                break;
        }

        header |= (!lsf) << 19;
        header |= (4 - layer) << 17;
        header |= 1 << 16; //no crc
        AV_WB32(out, header);
        if (size <= 0)
            return 2;  //we guess there is no crc, if there is one the user clearly does not care about overhead
        if (bitrate_index == 30)
            return -1;  //something is wrong ...

        header |= (bitrate_index >> 1) << 12;
        header |= sample_rate_index << 10;
        header |= (bitrate_index & 1) << 9;

        return 2; //FIXME actually put the needed ones in build_elision_headers()
        //return 3; //we guess that the private bit is not set
//FIXME the above assumptions should be checked, if these turn out false too often something should be done
    }
    return 0;
}