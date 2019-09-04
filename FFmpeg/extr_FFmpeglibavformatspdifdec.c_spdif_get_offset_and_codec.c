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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  enum IEC61937DataType { ____Placeholder_IEC61937DataType } IEC61937DataType ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AC3_FRAME_SIZE ; 
 int AVERROR_PATCHWELCOME ; 
 int AV_CODEC_ID_AAC ; 
 int AV_CODEC_ID_AC3 ; 
 int AV_CODEC_ID_DTS ; 
 int AV_CODEC_ID_MP1 ; 
 int AV_CODEC_ID_MP2 ; 
 int AV_CODEC_ID_MP3 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  IEC61937_AC3 138 
#define  IEC61937_DTS1 137 
#define  IEC61937_DTS2 136 
#define  IEC61937_DTS3 135 
#define  IEC61937_MPEG1_LAYER1 134 
#define  IEC61937_MPEG1_LAYER23 133 
#define  IEC61937_MPEG2_AAC 132 
#define  IEC61937_MPEG2_EXT 131 
#define  IEC61937_MPEG2_LAYER1_LSF 130 
#define  IEC61937_MPEG2_LAYER2_LSF 129 
#define  IEC61937_MPEG2_LAYER3_LSF 128 
 int av_adts_header_parse (char const*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ *,char*,int) ; 
 int** spdif_mpeg_pkt_offset ; 

__attribute__((used)) static int spdif_get_offset_and_codec(AVFormatContext *s,
                                      enum IEC61937DataType data_type,
                                      const char *buf, int *offset,
                                      enum AVCodecID *codec)
{
    uint32_t samples;
    uint8_t frames;
    int ret;

    switch (data_type & 0xff) {
    case IEC61937_AC3:
        *offset = AC3_FRAME_SIZE << 2;
        *codec = AV_CODEC_ID_AC3;
        break;
    case IEC61937_MPEG1_LAYER1:
        *offset = spdif_mpeg_pkt_offset[1][0];
        *codec = AV_CODEC_ID_MP1;
        break;
    case IEC61937_MPEG1_LAYER23:
        *offset = spdif_mpeg_pkt_offset[1][0];
        *codec = AV_CODEC_ID_MP3;
        break;
    case IEC61937_MPEG2_EXT:
        *offset = 4608;
        *codec = AV_CODEC_ID_MP3;
        break;
    case IEC61937_MPEG2_AAC:
        ret = av_adts_header_parse(buf, &samples, &frames);
        if (ret < 0) {
            if (s) /* be silent during a probe */
                av_log(s, AV_LOG_ERROR, "Invalid AAC packet in IEC 61937\n");
            return ret;
        }
        *offset = samples << 2;
        *codec = AV_CODEC_ID_AAC;
        break;
    case IEC61937_MPEG2_LAYER1_LSF:
        *offset = spdif_mpeg_pkt_offset[0][0];
        *codec = AV_CODEC_ID_MP1;
        break;
    case IEC61937_MPEG2_LAYER2_LSF:
        *offset = spdif_mpeg_pkt_offset[0][1];
        *codec = AV_CODEC_ID_MP2;
        break;
    case IEC61937_MPEG2_LAYER3_LSF:
        *offset = spdif_mpeg_pkt_offset[0][2];
        *codec = AV_CODEC_ID_MP3;
        break;
    case IEC61937_DTS1:
        *offset = 2048;
        *codec = AV_CODEC_ID_DTS;
        break;
    case IEC61937_DTS2:
        *offset = 4096;
        *codec = AV_CODEC_ID_DTS;
        break;
    case IEC61937_DTS3:
        *offset = 8192;
        *codec = AV_CODEC_ID_DTS;
        break;
    default:
        if (s) { /* be silent during a probe */
            avpriv_request_sample(s, "Data type 0x%04x in IEC 61937",
                                  data_type);
        }
        return AVERROR_PATCHWELCOME;
    }
    return 0;
}