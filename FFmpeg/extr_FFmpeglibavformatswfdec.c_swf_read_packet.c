#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct TYPE_22__ {int nb_streams; TYPE_3__** streams; int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_21__ {int size; int pts; int /*<<< orphan*/  stream_index; void* pos; scalar_t__ data; } ;
struct TYPE_20__ {int id; int /*<<< orphan*/  index; TYPE_1__* codecpar; void* skip_samples; int /*<<< orphan*/  duration; } ;
struct TYPE_19__ {int /*<<< orphan*/  frame_rate; void* samples_per_frame; } ;
struct TYPE_18__ {scalar_t__ codec_type; scalar_t__ codec_id; } ;
typedef  TYPE_2__ SWFContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_MJPEG ; 
 scalar_t__ AV_CODEC_ID_MP3 ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_RB32 (scalar_t__) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int /*<<< orphan*/ ,int) ; 
 int TAG_DEFINEBITSLOSSLESS ; 
 int TAG_DEFINEBITSLOSSLESS2 ; 
 int TAG_DEFINESOUND ; 
 int TAG_JPEG2 ; 
 int TAG_STREAMBLOCK ; 
 int TAG_STREAMHEAD ; 
 int TAG_STREAMHEAD2 ; 
 int TAG_VIDEOFRAME ; 
 int TAG_VIDEOSTREAM ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_new_packet (TYPE_4__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_4__*) ; 
 int /*<<< orphan*/  av_shrink_packet (TYPE_4__*,int) ; 
 TYPE_3__* avformat_new_stream (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,scalar_t__,int) ; 
 void* avio_rl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 void* avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* create_new_audio_stream (TYPE_5__*,int,int) ; 
 scalar_t__ ff_codec_get_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_swf_codec_tags ; 
 int get_swf_tag (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int swf_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    SWFContext *swf = s->priv_data;
    AVIOContext *pb = s->pb;
    AVStream *vst = NULL, *ast = NULL, *st = 0;
    int tag, len, i, frame, v, res;

#if CONFIG_ZLIB
    if (swf->zpb)
        pb = swf->zpb;
#endif

    for(;;) {
        uint64_t pos = avio_tell(pb);
        tag = get_swf_tag(pb, &len);
        if (tag < 0)
            return tag;
        if (len < 0) {
            av_log(s, AV_LOG_ERROR, "invalid tag length: %d\n", len);
            return AVERROR_INVALIDDATA;
        }
        if (tag == TAG_VIDEOSTREAM) {
            int ch_id = avio_rl16(pb);
            len -= 2;

            for (i=0; i<s->nb_streams; i++) {
                st = s->streams[i];
                if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && st->id == ch_id)
                    goto skip;
            }

            avio_rl16(pb);
            avio_rl16(pb);
            avio_rl16(pb);
            avio_r8(pb);
            /* Check for FLV1 */
            vst = avformat_new_stream(s, NULL);
            if (!vst)
                return AVERROR(ENOMEM);
            vst->id = ch_id;
            vst->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
            vst->codecpar->codec_id = ff_codec_get_id(ff_swf_codec_tags, avio_r8(pb));
            avpriv_set_pts_info(vst, 16, 256, swf->frame_rate);
            len -= 8;
        } else if (tag == TAG_STREAMHEAD || tag == TAG_STREAMHEAD2) {
            /* streaming found */

            for (i=0; i<s->nb_streams; i++) {
                st = s->streams[i];
                if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO && st->id == -1)
                    goto skip;
            }

            avio_r8(pb);
            v = avio_r8(pb);
            swf->samples_per_frame = avio_rl16(pb);
            ast = create_new_audio_stream(s, -1, v); /* -1 to avoid clash with video stream ch_id */
            if (!ast)
                return AVERROR(ENOMEM);
            len -= 4;
        } else if (tag == TAG_DEFINESOUND) {
            /* audio stream */
            int ch_id = avio_rl16(pb);

            for (i=0; i<s->nb_streams; i++) {
                st = s->streams[i];
                if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO && st->id == ch_id)
                    goto skip;
            }

            // FIXME: The entire audio stream is stored in a single chunk/tag. Normally,
            // these are smaller audio streams in DEFINESOUND tags, but it's technically
            // possible they could be huge. Break it up into multiple packets if it's big.
            v = avio_r8(pb);
            ast = create_new_audio_stream(s, ch_id, v);
            if (!ast)
                return AVERROR(ENOMEM);
            ast->duration = avio_rl32(pb); // number of samples
            if (((v>>4) & 15) == 2) { // MP3 sound data record
                ast->skip_samples = avio_rl16(pb);
                len -= 2;
            }
            len -= 7;
            if ((res = av_get_packet(pb, pkt, len)) < 0)
                return res;
            pkt->pos = pos;
            pkt->stream_index = ast->index;
            return pkt->size;
        } else if (tag == TAG_VIDEOFRAME) {
            int ch_id = avio_rl16(pb);
            len -= 2;
            for(i=0; i<s->nb_streams; i++) {
                st = s->streams[i];
                if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && st->id == ch_id) {
                    frame = avio_rl16(pb);
                    len -= 2;
                    if (len <= 0)
                        goto skip;
                    if ((res = av_get_packet(pb, pkt, len)) < 0)
                        return res;
                    pkt->pos = pos;
                    pkt->pts = frame;
                    pkt->stream_index = st->index;
                    return pkt->size;
                }
            }
        } else if (tag == TAG_DEFINEBITSLOSSLESS || tag == TAG_DEFINEBITSLOSSLESS2) {
#if CONFIG_ZLIB
            long out_len;
            uint8_t *buf = NULL, *zbuf = NULL, *pal;
            uint32_t colormap[AVPALETTE_COUNT] = {0};
            const int alpha_bmp = tag == TAG_DEFINEBITSLOSSLESS2;
            const int colormapbpp = 3 + alpha_bmp;
            int linesize, colormapsize = 0;

            const int ch_id   = avio_rl16(pb);
            const int bmp_fmt = avio_r8(pb);
            const int width   = avio_rl16(pb);
            const int height  = avio_rl16(pb);
            int pix_fmt;

            len -= 2+1+2+2;

            switch (bmp_fmt) {
            case 3: // PAL-8
                linesize = width;
                colormapsize = avio_r8(pb) + 1;
                len--;
                break;
            case 4: // RGB15
                linesize = width * 2;
                break;
            case 5: // RGB24 (0RGB)
                linesize = width * 4;
                break;
            default:
                av_log(s, AV_LOG_ERROR, "invalid bitmap format %d, skipped\n", bmp_fmt);
                goto bitmap_end_skip;
            }

            linesize = FFALIGN(linesize, 4);

            if (av_image_check_size(width, height, 0, s) < 0 ||
                linesize >= INT_MAX / height ||
                linesize * height >= INT_MAX - colormapsize * colormapbpp) {
                av_log(s, AV_LOG_ERROR, "invalid frame size %dx%d\n", width, height);
                goto bitmap_end_skip;
            }

            out_len = colormapsize * colormapbpp + linesize * height;

            ff_dlog(s, "bitmap: ch=%d fmt=%d %dx%d (linesize=%d) len=%d->%ld pal=%d\n",
                    ch_id, bmp_fmt, width, height, linesize, len, out_len, colormapsize);

            zbuf = av_malloc(len);
            buf  = av_malloc(out_len);
            if (!zbuf || !buf) {
                res = AVERROR(ENOMEM);
                goto bitmap_end;
            }

            len = avio_read(pb, zbuf, len);
            if (len < 0 || (res = uncompress(buf, &out_len, zbuf, len)) != Z_OK) {
                av_log(s, AV_LOG_WARNING, "Failed to uncompress one bitmap\n");
                goto bitmap_end_skip;
            }

            for (i = 0; i < s->nb_streams; i++) {
                st = s->streams[i];
                if (st->codecpar->codec_id == AV_CODEC_ID_RAWVIDEO && st->id == -3)
                    break;
            }
            if (i == s->nb_streams) {
                vst = avformat_new_stream(s, NULL);
                if (!vst) {
                    res = AVERROR(ENOMEM);
                    goto bitmap_end;
                }
                vst->id = -3; /* -3 to avoid clash with video stream and audio stream */
                vst->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
                vst->codecpar->codec_id = AV_CODEC_ID_RAWVIDEO;
                avpriv_set_pts_info(vst, 64, 256, swf->frame_rate);
                st = vst;
            }

            if ((res = av_new_packet(pkt, out_len - colormapsize * colormapbpp)) < 0)
                goto bitmap_end;
            if (!st->codecpar->width && !st->codecpar->height) {
                st->codecpar->width  = width;
                st->codecpar->height = height;
            } else {
                ff_add_param_change(pkt, 0, 0, 0, width, height);
            }
            pkt->pos = pos;
            pkt->stream_index = st->index;

            if (linesize * height > pkt->size) {
                res = AVERROR_INVALIDDATA;
                av_packet_unref(pkt);
                goto bitmap_end;
            }

            switch (bmp_fmt) {
            case 3:
                pix_fmt = AV_PIX_FMT_PAL8;
                for (i = 0; i < colormapsize; i++)
                    if (alpha_bmp)  colormap[i] = buf[3]<<24 | AV_RB24(buf + 4*i);
                    else            colormap[i] = 0xffU <<24 | AV_RB24(buf + 3*i);
                pal = av_packet_new_side_data(pkt, AV_PKT_DATA_PALETTE, AVPALETTE_SIZE);
                if (!pal) {
                    res = AVERROR(ENOMEM);
                    goto bitmap_end;
                }
                memcpy(pal, colormap, AVPALETTE_SIZE);
                break;
            case 4:
                pix_fmt = AV_PIX_FMT_RGB555;
                break;
            case 5:
                pix_fmt = alpha_bmp ? AV_PIX_FMT_ARGB : AV_PIX_FMT_0RGB;
                break;
            default:
                av_assert0(0);
            }
            if (st->codecpar->format != AV_PIX_FMT_NONE && st->codecpar->format != pix_fmt) {
                av_log(s, AV_LOG_ERROR, "pixel format change unsupported\n");
            } else
                st->codecpar->format = pix_fmt;

            memcpy(pkt->data, buf + colormapsize*colormapbpp, linesize * height);

            res = pkt->size;

bitmap_end:
            av_freep(&zbuf);
            av_freep(&buf);
            return res;
bitmap_end_skip:
            av_freep(&zbuf);
            av_freep(&buf);
#else
            av_log(s, AV_LOG_ERROR, "this file requires zlib support compiled in\n");
#endif
        } else if (tag == TAG_STREAMBLOCK) {
            for (i = 0; i < s->nb_streams; i++) {
                st = s->streams[i];
                if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO && st->id == -1) {
                    if (st->codecpar->codec_id == AV_CODEC_ID_MP3) {
                        avio_skip(pb, 4);
                        len -= 4;
                        if (len <= 0)
                            goto skip;
                        if ((res = av_get_packet(pb, pkt, len)) < 0)
                            return res;
                    } else { // ADPCM, PCM
                        if (len <= 0)
                            goto skip;
                        if ((res = av_get_packet(pb, pkt, len)) < 0)
                            return res;
                    }
                    pkt->pos          = pos;
                    pkt->stream_index = st->index;
                    return pkt->size;
                }
            }
        } else if (tag == TAG_JPEG2) {
            for (i=0; i<s->nb_streams; i++) {
                st = s->streams[i];
                if (st->codecpar->codec_id == AV_CODEC_ID_MJPEG && st->id == -2)
                    break;
            }
            if (i == s->nb_streams) {
                vst = avformat_new_stream(s, NULL);
                if (!vst)
                    return AVERROR(ENOMEM);
                vst->id = -2; /* -2 to avoid clash with video stream and audio stream */
                vst->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
                vst->codecpar->codec_id = AV_CODEC_ID_MJPEG;
                avpriv_set_pts_info(vst, 64, 256, swf->frame_rate);
                st = vst;
            }
            avio_rl16(pb); /* BITMAP_ID */
            len -= 2;
            if (len < 4)
                goto skip;
            if ((res = av_new_packet(pkt, len)) < 0)
                return res;
            if (avio_read(pb, pkt->data, 4) != 4) {
                av_packet_unref(pkt);
                return AVERROR_INVALIDDATA;
            }
            if (AV_RB32(pkt->data) == 0xffd8ffd9 ||
                AV_RB32(pkt->data) == 0xffd9ffd8) {
                /* old SWF files containing SOI/EOI as data start */
                /* files created by swink have reversed tag */
                pkt->size -= 4;
                memset(pkt->data+pkt->size, 0, 4);
                res = avio_read(pb, pkt->data, pkt->size);
            } else {
                res = avio_read(pb, pkt->data + 4, pkt->size - 4);
                if (res >= 0)
                    res += 4;
            }
            if (res != pkt->size) {
                if (res < 0) {
                    av_packet_unref(pkt);
                    return res;
                }
                av_shrink_packet(pkt, res);
            }

            pkt->pos = pos;
            pkt->stream_index = st->index;
            return pkt->size;
        } else {
            av_log(s, AV_LOG_DEBUG, "Unknown tag: %d\n", tag);
        }
    skip:
        if(len<0)
            av_log(s, AV_LOG_WARNING, "Clipping len %d\n", len);
        len = FFMAX(0, len);
        avio_skip(pb, len);
    }
}