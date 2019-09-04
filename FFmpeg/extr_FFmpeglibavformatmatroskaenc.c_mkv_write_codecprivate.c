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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {scalar_t__ codec_type; unsigned int codec_tag; scalar_t__ codec_id; scalar_t__ extradata_size; int /*<<< orphan*/  extradata; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_1__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_RAWVIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 unsigned int AV_RL32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FF_PUT_WAV_HEADER_FORCE_WAVEFORMATEX ; 
 int /*<<< orphan*/  MATROSKA_ID_CODECPRIVATE ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_get_name (scalar_t__) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ff_codec_bmp_tags ; 
 scalar_t__ ff_codec_get_id (int /*<<< orphan*/ ,unsigned int) ; 
 void* ff_codec_get_tag (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ff_codec_movvideo_tags ; 
 int /*<<< orphan*/  ff_codec_wav_tags ; 
 int /*<<< orphan*/  ff_put_bmp_header (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_put_wav_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int mkv_write_native_codecprivate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_ebml_binary (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mkv_write_codecprivate(AVFormatContext *s, AVIOContext *pb,
                                  AVCodecParameters *par,
                                  int native_id, int qt_id)
{
    AVIOContext *dyn_cp;
    uint8_t *codecpriv;
    int ret, codecpriv_size;

    ret = avio_open_dyn_buf(&dyn_cp);
    if (ret < 0)
        return ret;

    if (native_id) {
        ret = mkv_write_native_codecprivate(s, pb, par, dyn_cp);
    } else if (par->codec_type == AVMEDIA_TYPE_VIDEO) {
        if (qt_id) {
            if (!par->codec_tag)
                par->codec_tag = ff_codec_get_tag(ff_codec_movvideo_tags,
                                                    par->codec_id);
            if (   ff_codec_get_id(ff_codec_movvideo_tags, par->codec_tag) == par->codec_id
                && (!par->extradata_size || ff_codec_get_id(ff_codec_movvideo_tags, AV_RL32(par->extradata + 4)) != par->codec_id)
            ) {
                int i;
                avio_wb32(dyn_cp, 0x5a + par->extradata_size);
                avio_wl32(dyn_cp, par->codec_tag);
                for(i = 0; i < 0x5a - 8; i++)
                    avio_w8(dyn_cp, 0);
            }
            avio_write(dyn_cp, par->extradata, par->extradata_size);
        } else {
            if (!ff_codec_get_tag(ff_codec_bmp_tags, par->codec_id))
                av_log(s, AV_LOG_WARNING, "codec %s is not supported by this format\n",
                       avcodec_get_name(par->codec_id));

            if (!par->codec_tag)
                par->codec_tag = ff_codec_get_tag(ff_codec_bmp_tags,
                                                  par->codec_id);
            if (!par->codec_tag && par->codec_id != AV_CODEC_ID_RAWVIDEO) {
                av_log(s, AV_LOG_ERROR, "No bmp codec tag found for codec %s\n",
                       avcodec_get_name(par->codec_id));
                ret = AVERROR(EINVAL);
            }

            ff_put_bmp_header(dyn_cp, par, 0, 0);
        }
    } else if (par->codec_type == AVMEDIA_TYPE_AUDIO) {
        unsigned int tag;
        tag = ff_codec_get_tag(ff_codec_wav_tags, par->codec_id);
        if (!tag) {
            av_log(s, AV_LOG_ERROR, "No wav codec tag found for codec %s\n",
                   avcodec_get_name(par->codec_id));
            ret = AVERROR(EINVAL);
        }
        if (!par->codec_tag)
            par->codec_tag = tag;

        ff_put_wav_header(s, dyn_cp, par, FF_PUT_WAV_HEADER_FORCE_WAVEFORMATEX);
    }

    codecpriv_size = avio_close_dyn_buf(dyn_cp, &codecpriv);
    if (codecpriv_size)
        put_ebml_binary(pb, MATROSKA_ID_CODECPRIVATE, codecpriv,
                        codecpriv_size);
    av_free(codecpriv);
    return ret;
}