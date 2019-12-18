#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_18__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_20__ {int tv_nsec; } ;
struct stat {TYPE_1__ st_mtim; scalar_t__ st_mtime; } ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  header ;
typedef  int /*<<< orphan*/  filename_bytes ;
struct TYPE_21__ {char** gl_pathv; } ;
struct TYPE_22__ {size_t img_number; size_t img_last; size_t img_first; scalar_t__ pattern_type; int frame_size; int ts_from_file; int pts; scalar_t__ is_pipe; int /*<<< orphan*/  img_count; scalar_t__ loop; int /*<<< orphan*/  split_planes; int /*<<< orphan*/  path; TYPE_2__ globstate; scalar_t__ use_glob; } ;
typedef  TYPE_3__ VideoDemuxData ;
struct TYPE_27__ {scalar_t__ codec_id; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_26__ {scalar_t__ (* io_open ) (TYPE_7__*,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * pb; TYPE_18__** streams; TYPE_3__* priv_data; } ;
struct TYPE_25__ {scalar_t__ read_packet; scalar_t__ raw_codec_id; } ;
struct TYPE_24__ {int pts; int size; int /*<<< orphan*/ * data; int /*<<< orphan*/  pos; int /*<<< orphan*/  flags; scalar_t__ stream_index; } ;
struct TYPE_23__ {int buf_size; char* filename; int /*<<< orphan*/ * buf; int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {int /*<<< orphan*/  parser; TYPE_8__* codecpar; } ;
typedef  TYPE_4__ AVProbeData ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVInputFormat ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_7__ AVFormatContext ;
typedef  TYPE_8__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AVINDEX_KEYFRAME ; 
 int /*<<< orphan*/  AVIO_FLAG_READ ; 
 int AVPROBE_PADDING_SIZE ; 
 scalar_t__ AV_CODEC_ID_NONE ; 
 scalar_t__ AV_CODEC_ID_RAWVIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EIO ; 
 int PROBE_BUF_MIN ; 
 scalar_t__ PT_NONE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_add_index_entry (TYPE_18__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ av_get_frame_filename (char*,int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,char*) ; 
 int av_new_packet (TYPE_5__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_5__*) ; 
 TYPE_6__* av_probe_input_format3 (TYPE_4__*,int,int*) ; 
 int /*<<< orphan*/  av_strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avio_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_format_io_close (TYPE_7__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  infer_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ stub1 (TYPE_7__*,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ff_img_read_packet(AVFormatContext *s1, AVPacket *pkt)
{
    VideoDemuxData *s = s1->priv_data;
    char filename_bytes[1024];
    char *filename = filename_bytes;
    int i, res;
    int size[3]           = { 0 }, ret[3] = { 0 };
    AVIOContext *f[3]     = { NULL };
    AVCodecParameters *par = s1->streams[0]->codecpar;

    if (!s->is_pipe) {
        /* loop over input */
        if (s->loop && s->img_number > s->img_last) {
            s->img_number = s->img_first;
        }
        if (s->img_number > s->img_last)
            return AVERROR_EOF;
        if (s->pattern_type == PT_NONE) {
            av_strlcpy(filename_bytes, s->path, sizeof(filename_bytes));
        } else if (s->use_glob) {
#if HAVE_GLOB
            filename = s->globstate.gl_pathv[s->img_number];
#endif
        } else {
        if (av_get_frame_filename(filename_bytes, sizeof(filename_bytes),
                                  s->path,
                                  s->img_number) < 0 && s->img_number > 1)
            return AVERROR(EIO);
        }
        for (i = 0; i < 3; i++) {
            if (s1->pb &&
                !strcmp(filename_bytes, s->path) &&
                !s->loop &&
                !s->split_planes) {
                f[i] = s1->pb;
            } else if (s1->io_open(s1, &f[i], filename, AVIO_FLAG_READ, NULL) < 0) {
                if (i >= 1)
                    break;
                av_log(s1, AV_LOG_ERROR, "Could not open file : %s\n",
                       filename);
                return AVERROR(EIO);
            }
            size[i] = avio_size(f[i]);

            if (!s->split_planes)
                break;
            filename[strlen(filename) - 1] = 'U' + i;
        }

        if (par->codec_id == AV_CODEC_ID_NONE) {
            AVProbeData pd = { 0 };
            const AVInputFormat *ifmt;
            uint8_t header[PROBE_BUF_MIN + AVPROBE_PADDING_SIZE];
            int ret;
            int score = 0;

            ret = avio_read(f[0], header, PROBE_BUF_MIN);
            if (ret < 0)
                return ret;
            memset(header + ret, 0, sizeof(header) - ret);
            avio_skip(f[0], -ret);
            pd.buf = header;
            pd.buf_size = ret;
            pd.filename = filename;

            ifmt = av_probe_input_format3(&pd, 1, &score);
            if (ifmt && ifmt->read_packet == ff_img_read_packet && ifmt->raw_codec_id)
                par->codec_id = ifmt->raw_codec_id;
        }

        if (par->codec_id == AV_CODEC_ID_RAWVIDEO && !par->width)
            infer_size(&par->width, &par->height, size[0]);
    } else {
        f[0] = s1->pb;
        if (avio_feof(f[0]) && s->loop && s->is_pipe)
            avio_seek(f[0], 0, SEEK_SET);
        if (avio_feof(f[0]))
            return AVERROR_EOF;
        if (s->frame_size > 0) {
            size[0] = s->frame_size;
        } else if (!s1->streams[0]->parser) {
            size[0] = avio_size(s1->pb);
        } else {
            size[0] = 4096;
        }
    }

    res = av_new_packet(pkt, size[0] + size[1] + size[2]);
    if (res < 0) {
        goto fail;
    }
    pkt->stream_index = 0;
    pkt->flags       |= AV_PKT_FLAG_KEY;
    if (s->ts_from_file) {
        struct stat img_stat;
        if (stat(filename, &img_stat)) {
            res = AVERROR(EIO);
            goto fail;
        }
        pkt->pts = (int64_t)img_stat.st_mtime;
#if HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC
        if (s->ts_from_file == 2)
            pkt->pts = 1000000000*pkt->pts + img_stat.st_mtim.tv_nsec;
#endif
        av_add_index_entry(s1->streams[0], s->img_number, pkt->pts, 0, 0, AVINDEX_KEYFRAME);
    } else if (!s->is_pipe) {
        pkt->pts      = s->pts;
    }

    if (s->is_pipe)
        pkt->pos = avio_tell(f[0]);

    pkt->size = 0;
    for (i = 0; i < 3; i++) {
        if (f[i]) {
            ret[i] = avio_read(f[i], pkt->data + pkt->size, size[i]);
            if (s->loop && s->is_pipe && ret[i] == AVERROR_EOF) {
                if (avio_seek(f[i], 0, SEEK_SET) >= 0) {
                    pkt->pos = 0;
                    ret[i] = avio_read(f[i], pkt->data + pkt->size, size[i]);
                }
            }
            if (!s->is_pipe && f[i] != s1->pb)
                ff_format_io_close(s1, &f[i]);
            if (ret[i] > 0)
                pkt->size += ret[i];
        }
    }

    if (ret[0] <= 0 || ret[1] < 0 || ret[2] < 0) {
        av_packet_unref(pkt);
        if (ret[0] < 0) {
            res = ret[0];
        } else if (ret[1] < 0) {
            res = ret[1];
        } else if (ret[2] < 0) {
            res = ret[2];
        } else {
            res = AVERROR_EOF;
        }
        goto fail;
    } else {
        s->img_count++;
        s->img_number++;
        s->pts++;
        return 0;
    }

fail:
    if (!s->is_pipe) {
        for (i = 0; i < 3; i++) {
            if (f[i] != s1->pb)
                ff_format_io_close(s1, &f[i]);
        }
    }
    return res;
}