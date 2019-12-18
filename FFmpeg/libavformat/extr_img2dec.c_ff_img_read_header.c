#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_17__ {int gl_pathc; } ;
struct TYPE_19__ {int den; int num; } ;
struct TYPE_21__ {char* path; int img_number; int is_pipe; int ts_from_file; int use_glob; int img_first; int img_last; int /*<<< orphan*/  split_planes; scalar_t__ pattern_type; TYPE_10__ globstate; scalar_t__ start_number_range; scalar_t__ start_number; scalar_t__ height; scalar_t__ width; TYPE_2__ framerate; scalar_t__ img_count; scalar_t__ pixel_format; } ;
typedef  TYPE_4__ VideoDemuxData ;
struct TYPE_25__ {scalar_t__ video_codec_id; scalar_t__ audio_codec_id; int flags; scalar_t__ pb; int /*<<< orphan*/  url; TYPE_1__* iformat; int /*<<< orphan*/  ctx_flags; TYPE_4__* priv_data; } ;
struct TYPE_24__ {scalar_t__ read_header; scalar_t__ (* read_probe ) (TYPE_6__*) ;int flags; scalar_t__ raw_codec_id; } ;
struct TYPE_23__ {char* buf; int buf_size; int /*<<< orphan*/  filename; int /*<<< orphan*/  member_0; } ;
struct TYPE_22__ {int duration; TYPE_3__* codecpar; scalar_t__ start_time; int /*<<< orphan*/  need_parsing; } ;
struct TYPE_20__ {scalar_t__ codec_type; scalar_t__ codec_id; int format; scalar_t__ height; scalar_t__ width; } ;
struct TYPE_18__ {int flags; scalar_t__ raw_codec_id; } ;
typedef  TYPE_5__ AVStream ;
typedef  TYPE_6__ AVProbeData ;
typedef  TYPE_7__ AVInputFormat ;
typedef  TYPE_8__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVFMTCTX_NOHEADER ; 
 int AVFMT_FLAG_CUSTOM_IO ; 
 int AVFMT_NOFILE ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AVPROBE_PADDING_SIZE ; 
 int /*<<< orphan*/  AVSTREAM_PARSE_FULL ; 
 scalar_t__ AV_CODEC_ID_ALIAS_PIX ; 
 scalar_t__ AV_CODEC_ID_LJPEG ; 
 scalar_t__ AV_CODEC_ID_MJPEG ; 
 scalar_t__ AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int GLOB_BRACE ; 
 int GLOB_NOCHECK ; 
 int GLOB_NOMAGIC ; 
 scalar_t__ PT_DEFAULT ; 
 scalar_t__ PT_GLOB ; 
 scalar_t__ PT_GLOB_SEQUENCE ; 
 scalar_t__ PT_NONE ; 
 scalar_t__ PT_SEQUENCE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_7__* av_demuxer_iterate (void**) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int av_get_pix_fmt (scalar_t__) ; 
 int /*<<< orphan*/  av_log (TYPE_8__*,int /*<<< orphan*/ ,char*,...) ; 
 char* av_realloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  av_strcasecmp (char const*,char*) ; 
 char* av_strdup (char*) ; 
 int /*<<< orphan*/  av_strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* avformat_new_stream (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int avio_read (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  avio_seek (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_5__*,int,int,int) ; 
 scalar_t__ ff_guess_image2_codec (char*) ; 
 int /*<<< orphan*/  ffio_rewind_with_probe_data (scalar_t__,char**,int) ; 
 scalar_t__ find_image_range (scalar_t__,int*,int*,char*,scalar_t__,scalar_t__) ; 
 int glob (char*,int,int /*<<< orphan*/ *,TYPE_10__*) ; 
 int is_glob (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ strspn (char*,char*) ; 
 scalar_t__ stub1 (TYPE_6__*) ; 

int ff_img_read_header(AVFormatContext *s1)
{
    VideoDemuxData *s = s1->priv_data;
    int first_index = 1, last_index = 1;
    AVStream *st;
    enum AVPixelFormat pix_fmt = AV_PIX_FMT_NONE;

    s1->ctx_flags |= AVFMTCTX_NOHEADER;

    st = avformat_new_stream(s1, NULL);
    if (!st) {
        return AVERROR(ENOMEM);
    }

    if (s->pixel_format &&
        (pix_fmt = av_get_pix_fmt(s->pixel_format)) == AV_PIX_FMT_NONE) {
        av_log(s1, AV_LOG_ERROR, "No such pixel format: %s.\n",
               s->pixel_format);
        return AVERROR(EINVAL);
    }

    av_strlcpy(s->path, s1->url, sizeof(s->path));
    s->img_number = 0;
    s->img_count  = 0;

    /* find format */
    if (s1->iformat->flags & AVFMT_NOFILE)
        s->is_pipe = 0;
    else {
        s->is_pipe       = 1;
        st->need_parsing = AVSTREAM_PARSE_FULL;
    }

    if (s->ts_from_file == 2) {
#if !HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC
        av_log(s1, AV_LOG_ERROR, "POSIX.1-2008 not supported, nanosecond file timestamps unavailable\n");
        return AVERROR(ENOSYS);
#endif
        avpriv_set_pts_info(st, 64, 1, 1000000000);
    } else if (s->ts_from_file)
        avpriv_set_pts_info(st, 64, 1, 1);
    else
        avpriv_set_pts_info(st, 64, s->framerate.den, s->framerate.num);

    if (s->width && s->height) {
        st->codecpar->width  = s->width;
        st->codecpar->height = s->height;
    }

    if (!s->is_pipe) {
        if (s->pattern_type == PT_DEFAULT) {
            if (s1->pb) {
                s->pattern_type = PT_NONE;
            } else
                s->pattern_type = PT_GLOB_SEQUENCE;
        }

        if (s->pattern_type == PT_GLOB_SEQUENCE) {
        s->use_glob = is_glob(s->path);
        if (s->use_glob) {
#if HAVE_GLOB
            char *p = s->path, *q, *dup;
            int gerr;
#endif

            av_log(s1, AV_LOG_WARNING, "Pattern type 'glob_sequence' is deprecated: "
                   "use pattern_type 'glob' instead\n");
#if HAVE_GLOB
            dup = q = av_strdup(p);
            while (*q) {
                /* Do we have room for the next char and a \ insertion? */
                if ((p - s->path) >= (sizeof(s->path) - 2))
                  break;
                if (*q == '%' && strspn(q + 1, "%*?[]{}"))
                    ++q;
                else if (strspn(q, "\\*?[]{}"))
                    *p++ = '\\';
                *p++ = *q++;
            }
            *p = 0;
            av_free(dup);

            gerr = glob(s->path, GLOB_NOCHECK|GLOB_BRACE|GLOB_NOMAGIC, NULL, &s->globstate);
            if (gerr != 0) {
                return AVERROR(ENOENT);
            }
            first_index = 0;
            last_index = s->globstate.gl_pathc - 1;
#endif
        }
        }
        if ((s->pattern_type == PT_GLOB_SEQUENCE && !s->use_glob) || s->pattern_type == PT_SEQUENCE) {
            if (find_image_range(s1->pb, &first_index, &last_index, s->path,
                                 s->start_number, s->start_number_range) < 0) {
                av_log(s1, AV_LOG_ERROR,
                       "Could find no file with path '%s' and index in the range %d-%d\n",
                       s->path, s->start_number, s->start_number + s->start_number_range - 1);
                return AVERROR(ENOENT);
            }
        } else if (s->pattern_type == PT_GLOB) {
#if HAVE_GLOB
            int gerr;
            gerr = glob(s->path, GLOB_NOCHECK|GLOB_BRACE|GLOB_NOMAGIC, NULL, &s->globstate);
            if (gerr != 0) {
                return AVERROR(ENOENT);
            }
            first_index = 0;
            last_index = s->globstate.gl_pathc - 1;
            s->use_glob = 1;
#else
            av_log(s1, AV_LOG_ERROR,
                   "Pattern type 'glob' was selected but globbing "
                   "is not supported by this libavformat build\n");
            return AVERROR(ENOSYS);
#endif
        } else if (s->pattern_type != PT_GLOB_SEQUENCE && s->pattern_type != PT_NONE) {
            av_log(s1, AV_LOG_ERROR,
                   "Unknown value '%d' for pattern_type option\n", s->pattern_type);
            return AVERROR(EINVAL);
        }
        s->img_first  = first_index;
        s->img_last   = last_index;
        s->img_number = first_index;
        /* compute duration */
        if (!s->ts_from_file) {
            st->start_time = 0;
            st->duration   = last_index - first_index + 1;
        }
    }

    if (s1->video_codec_id) {
        st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
        st->codecpar->codec_id   = s1->video_codec_id;
    } else if (s1->audio_codec_id) {
        st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
        st->codecpar->codec_id   = s1->audio_codec_id;
    } else if (s1->iformat->raw_codec_id) {
        st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
        st->codecpar->codec_id   = s1->iformat->raw_codec_id;
    } else {
        const char *str = strrchr(s->path, '.');
        s->split_planes       = str && !av_strcasecmp(str + 1, "y");
        st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
        if (s1->pb) {
            int probe_buffer_size = 2048;
            uint8_t *probe_buffer = av_realloc(NULL, probe_buffer_size + AVPROBE_PADDING_SIZE);
            const AVInputFormat *fmt = NULL;
            void *fmt_iter = NULL;
            AVProbeData pd = { 0 };

            if (!probe_buffer)
                return AVERROR(ENOMEM);

            probe_buffer_size = avio_read(s1->pb, probe_buffer, probe_buffer_size);
            if (probe_buffer_size < 0) {
                av_free(probe_buffer);
                return probe_buffer_size;
            }
            memset(probe_buffer + probe_buffer_size, 0, AVPROBE_PADDING_SIZE);

            pd.buf = probe_buffer;
            pd.buf_size = probe_buffer_size;
            pd.filename = s1->url;

            while ((fmt = av_demuxer_iterate(&fmt_iter))) {
                if (fmt->read_header != ff_img_read_header ||
                    !fmt->read_probe ||
                    (fmt->flags & AVFMT_NOFILE) ||
                    !fmt->raw_codec_id)
                    continue;
                if (fmt->read_probe(&pd) > 0) {
                    st->codecpar->codec_id = fmt->raw_codec_id;
                    break;
                }
            }
            if (s1->flags & AVFMT_FLAG_CUSTOM_IO) {
                avio_seek(s1->pb, 0, SEEK_SET);
                av_freep(&probe_buffer);
            } else
                ffio_rewind_with_probe_data(s1->pb, &probe_buffer, probe_buffer_size);
        }
        if (st->codecpar->codec_id == AV_CODEC_ID_NONE)
            st->codecpar->codec_id = ff_guess_image2_codec(s->path);
        if (st->codecpar->codec_id == AV_CODEC_ID_LJPEG)
            st->codecpar->codec_id = AV_CODEC_ID_MJPEG;
        if (st->codecpar->codec_id == AV_CODEC_ID_ALIAS_PIX) // we cannot distingiush this from BRENDER_PIX
            st->codecpar->codec_id = AV_CODEC_ID_NONE;
    }
    if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO &&
        pix_fmt != AV_PIX_FMT_NONE)
        st->codecpar->format = pix_fmt;

    return 0;
}