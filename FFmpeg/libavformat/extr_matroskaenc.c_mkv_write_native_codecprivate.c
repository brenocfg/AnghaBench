#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int codec_id; int extradata_size; int /*<<< orphan*/  extradata; int /*<<< orphan*/  codec_tag; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_1__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
#define  AV_CODEC_ID_AAC 136 
#define  AV_CODEC_ID_ALAC 135 
#define  AV_CODEC_ID_AV1 134 
#define  AV_CODEC_ID_FLAC 133 
#define  AV_CODEC_ID_H264 132 
#define  AV_CODEC_ID_HEVC 131 
 int AV_CODEC_ID_PRORES ; 
#define  AV_CODEC_ID_THEORA 130 
 int AV_CODEC_ID_TTA ; 
#define  AV_CODEC_ID_VORBIS 129 
#define  AV_CODEC_ID_WAVPACK 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  MAX_PCE_SIZE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ff_codec_get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_codec_movvideo_tags ; 
 int ff_isom_write_av1c (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ff_isom_write_avcc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_isom_write_hvcc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ebml_void (int /*<<< orphan*/ *,int) ; 
 int put_flac_codecpriv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int put_wv_codecpriv (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int put_xiph_codecpriv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int mkv_write_native_codecprivate(AVFormatContext *s, AVIOContext *pb,
                                         AVCodecParameters *par,
                                         AVIOContext *dyn_cp)
{
    switch (par->codec_id) {
    case AV_CODEC_ID_VORBIS:
    case AV_CODEC_ID_THEORA:
        return put_xiph_codecpriv(s, dyn_cp, par);
    case AV_CODEC_ID_FLAC:
        return put_flac_codecpriv(s, dyn_cp, par);
    case AV_CODEC_ID_WAVPACK:
        return put_wv_codecpriv(dyn_cp, par);
    case AV_CODEC_ID_H264:
        return ff_isom_write_avcc(dyn_cp, par->extradata,
                                  par->extradata_size);
    case AV_CODEC_ID_HEVC:
        ff_isom_write_hvcc(dyn_cp, par->extradata,
                           par->extradata_size, 0);
        return 0;
    case AV_CODEC_ID_AV1:
        if (par->extradata_size)
            return ff_isom_write_av1c(dyn_cp, par->extradata,
                                      par->extradata_size);
        else
            put_ebml_void(pb, 4 + 3);
        break;
    case AV_CODEC_ID_ALAC:
        if (par->extradata_size < 36) {
            av_log(s, AV_LOG_ERROR,
                   "Invalid extradata found, ALAC expects a 36-byte "
                   "QuickTime atom.");
            return AVERROR_INVALIDDATA;
        } else
            avio_write(dyn_cp, par->extradata + 12,
                       par->extradata_size - 12);
        break;
    case AV_CODEC_ID_AAC:
        if (par->extradata_size)
            avio_write(dyn_cp, par->extradata, par->extradata_size);
        else
            put_ebml_void(pb, MAX_PCE_SIZE + 2 + 4);
        break;
    default:
        if (par->codec_id == AV_CODEC_ID_PRORES &&
            ff_codec_get_id(ff_codec_movvideo_tags, par->codec_tag) == AV_CODEC_ID_PRORES) {
            avio_wl32(dyn_cp, par->codec_tag);
        } else if (par->extradata_size && par->codec_id != AV_CODEC_ID_TTA)
            avio_write(dyn_cp, par->extradata, par->extradata_size);
    }

    return 0;
}