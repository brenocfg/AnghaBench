#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__** streams; TYPE_3__* priv_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  hd_buf; int /*<<< orphan*/  header_info; } ;
struct TYPE_8__ {int codec_id; } ;
struct TYPE_7__ {TYPE_2__* codecpar; } ;
typedef  TYPE_3__ IEC61937Context ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_PATCHWELCOME ; 
#define  AV_CODEC_ID_AAC 136 
#define  AV_CODEC_ID_AC3 135 
#define  AV_CODEC_ID_DTS 134 
#define  AV_CODEC_ID_EAC3 133 
#define  AV_CODEC_ID_MLP 132 
#define  AV_CODEC_ID_MP1 131 
#define  AV_CODEC_ID_MP2 130 
#define  AV_CODEC_ID_MP3 129 
#define  AV_CODEC_ID_TRUEHD 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  MAT_FRAME_SIZE ; 
 int /*<<< orphan*/  av_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  spdif_header_aac ; 
 int /*<<< orphan*/  spdif_header_ac3 ; 
 int /*<<< orphan*/  spdif_header_dts ; 
 int /*<<< orphan*/  spdif_header_eac3 ; 
 int /*<<< orphan*/  spdif_header_mpeg ; 
 int /*<<< orphan*/  spdif_header_truehd ; 

__attribute__((used)) static int spdif_write_header(AVFormatContext *s)
{
    IEC61937Context *ctx = s->priv_data;

    switch (s->streams[0]->codecpar->codec_id) {
    case AV_CODEC_ID_AC3:
        ctx->header_info = spdif_header_ac3;
        break;
    case AV_CODEC_ID_EAC3:
        ctx->header_info = spdif_header_eac3;
        break;
    case AV_CODEC_ID_MP1:
    case AV_CODEC_ID_MP2:
    case AV_CODEC_ID_MP3:
        ctx->header_info = spdif_header_mpeg;
        break;
    case AV_CODEC_ID_DTS:
        ctx->header_info = spdif_header_dts;
        break;
    case AV_CODEC_ID_AAC:
        ctx->header_info = spdif_header_aac;
        break;
    case AV_CODEC_ID_TRUEHD:
    case AV_CODEC_ID_MLP:
        ctx->header_info = spdif_header_truehd;
        ctx->hd_buf = av_malloc(MAT_FRAME_SIZE);
        if (!ctx->hd_buf)
            return AVERROR(ENOMEM);
        break;
    default:
        avpriv_report_missing_feature(s, "Codec %d",
                                      s->streams[0]->codecpar->codec_id);
        return AVERROR_PATCHWELCOME;
    }
    return 0;
}