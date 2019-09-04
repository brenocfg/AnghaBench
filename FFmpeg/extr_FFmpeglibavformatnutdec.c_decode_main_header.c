#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {unsigned int num; unsigned int den; } ;
typedef  TYPE_2__ uint8_t ;
typedef  int uint64_t ;
struct TYPE_25__ {TYPE_4__* pb; } ;
struct TYPE_24__ {scalar_t__ eof_reached; } ;
struct TYPE_23__ {int version; int max_distance; unsigned int time_base_count; unsigned int header_count; unsigned int* header_len; TYPE_2__** header; TYPE_2__* time_base; int /*<<< orphan*/  stream; void* flags; TYPE_1__* frame_code; void* minor_version; TYPE_5__* avf; } ;
struct TYPE_21__ {int flags; int pts_delta; int stream_id; int size_mul; int size_lsb; int reserved_count; int header_idx; } ;
typedef  int /*<<< orphan*/  StreamContext ;
typedef  TYPE_3__ NUTContext ;
typedef  int /*<<< orphan*/  AVRational ;
typedef  TYPE_4__ AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int FLAG_INVALID ; 
 int /*<<< orphan*/  GET_V (unsigned int,int) ; 
 int INT_MAX ; 
 int /*<<< orphan*/  MAIN_STARTCODE ; 
 int NUT_MAX_STREAMS ; 
 int NUT_MAX_VERSION ; 
 int NUT_MIN_VERSION ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_calloc (unsigned int,int) ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 int av_gcd (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* av_malloc (int) ; 
 TYPE_2__* av_malloc_array (unsigned int,int) ; 
 int /*<<< orphan*/  avformat_new_stream (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_read (TYPE_4__*,TYPE_2__*,int) ; 
 int avio_tell (TYPE_4__*) ; 
 scalar_t__ ffio_get_checksum (TYPE_4__*) ; 
 void* ffio_read_varlen (TYPE_4__*) ; 
 int get_packetheader (TYPE_3__*,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int get_s (TYPE_4__*) ; 
 scalar_t__ skip_reserved (TYPE_4__*,int) ; 

__attribute__((used)) static int decode_main_header(NUTContext *nut)
{
    AVFormatContext *s = nut->avf;
    AVIOContext *bc    = s->pb;
    uint64_t tmp, end;
    unsigned int stream_count;
    int i, j, count, ret;
    int tmp_stream, tmp_mul, tmp_pts, tmp_size, tmp_res, tmp_head_idx;

    end  = get_packetheader(nut, bc, 1, MAIN_STARTCODE);
    end += avio_tell(bc);

    nut->version = ffio_read_varlen(bc);
    if (nut->version < NUT_MIN_VERSION ||
        nut->version > NUT_MAX_VERSION) {
        av_log(s, AV_LOG_ERROR, "Version %d not supported.\n",
               nut->version);
        return AVERROR(ENOSYS);
    }
    if (nut->version > 3)
        nut->minor_version = ffio_read_varlen(bc);

    GET_V(stream_count, tmp > 0 && tmp <= NUT_MAX_STREAMS);

    nut->max_distance = ffio_read_varlen(bc);
    if (nut->max_distance > 65536) {
        av_log(s, AV_LOG_DEBUG, "max_distance %d\n", nut->max_distance);
        nut->max_distance = 65536;
    }

    GET_V(nut->time_base_count, tmp > 0 && tmp < INT_MAX / sizeof(AVRational));
    nut->time_base = av_malloc_array(nut->time_base_count, sizeof(AVRational));
    if (!nut->time_base)
        return AVERROR(ENOMEM);

    for (i = 0; i < nut->time_base_count; i++) {
        GET_V(nut->time_base[i].num, tmp > 0 && tmp < (1ULL << 31));
        GET_V(nut->time_base[i].den, tmp > 0 && tmp < (1ULL << 31));
        if (av_gcd(nut->time_base[i].num, nut->time_base[i].den) != 1) {
            av_log(s, AV_LOG_ERROR, "invalid time base %d/%d\n",
                   nut->time_base[i].num,
                   nut->time_base[i].den);
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }
    }
    tmp_pts      = 0;
    tmp_mul      = 1;
    tmp_stream   = 0;
    tmp_head_idx = 0;
    for (i = 0; i < 256;) {
        int tmp_flags  = ffio_read_varlen(bc);
        int tmp_fields = ffio_read_varlen(bc);

        if (tmp_fields > 0)
            tmp_pts = get_s(bc);
        if (tmp_fields > 1)
            tmp_mul = ffio_read_varlen(bc);
        if (tmp_fields > 2)
            tmp_stream = ffio_read_varlen(bc);
        if (tmp_fields > 3)
            tmp_size = ffio_read_varlen(bc);
        else
            tmp_size = 0;
        if (tmp_fields > 4)
            tmp_res = ffio_read_varlen(bc);
        else
            tmp_res = 0;
        if (tmp_fields > 5)
            count = ffio_read_varlen(bc);
        else
            count = tmp_mul - tmp_size;
        if (tmp_fields > 6)
            get_s(bc);
        if (tmp_fields > 7)
            tmp_head_idx = ffio_read_varlen(bc);

        while (tmp_fields-- > 8) {
            if (bc->eof_reached) {
                av_log(s, AV_LOG_ERROR, "reached EOF while decoding main header\n");
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }
            ffio_read_varlen(bc);
        }

        if (count <= 0 || count > 256 - (i <= 'N') - i) {
            av_log(s, AV_LOG_ERROR, "illegal count %d at %d\n", count, i);
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }
        if (tmp_stream >= stream_count) {
            av_log(s, AV_LOG_ERROR, "illegal stream number %d >= %d\n",
                   tmp_stream, stream_count);
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }

        for (j = 0; j < count; j++, i++) {
            if (i == 'N') {
                nut->frame_code[i].flags = FLAG_INVALID;
                j--;
                continue;
            }
            nut->frame_code[i].flags          = tmp_flags;
            nut->frame_code[i].pts_delta      = tmp_pts;
            nut->frame_code[i].stream_id      = tmp_stream;
            nut->frame_code[i].size_mul       = tmp_mul;
            nut->frame_code[i].size_lsb       = tmp_size + j;
            nut->frame_code[i].reserved_count = tmp_res;
            nut->frame_code[i].header_idx     = tmp_head_idx;
        }
    }
    av_assert0(nut->frame_code['N'].flags == FLAG_INVALID);

    if (end > avio_tell(bc) + 4) {
        int rem = 1024;
        GET_V(nut->header_count, tmp < 128U);
        nut->header_count++;
        for (i = 1; i < nut->header_count; i++) {
            uint8_t *hdr;
            GET_V(nut->header_len[i], tmp > 0 && tmp < 256);
            if (rem < nut->header_len[i]) {
                av_log(s, AV_LOG_ERROR,
                       "invalid elision header %d : %d > %d\n",
                       i, nut->header_len[i], rem);
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }
            rem -= nut->header_len[i];
            hdr = av_malloc(nut->header_len[i]);
            if (!hdr) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            avio_read(bc, hdr, nut->header_len[i]);
            nut->header[i] = hdr;
        }
        av_assert0(nut->header_len[0] == 0);
    }

    // flags had been effectively introduced in version 4
    if (nut->version > 3 && end > avio_tell(bc) + 4) {
        nut->flags = ffio_read_varlen(bc);
    }

    if (skip_reserved(bc, end) || ffio_get_checksum(bc)) {
        av_log(s, AV_LOG_ERROR, "main header checksum mismatch\n");
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    nut->stream = av_calloc(stream_count, sizeof(StreamContext));
    if (!nut->stream) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    for (i = 0; i < stream_count; i++)
        avformat_new_stream(s, NULL);

    return 0;
fail:
    av_freep(&nut->time_base);
    for (i = 1; i < nut->header_count; i++) {
        av_freep(&nut->header[i]);
    }
    nut->header_count = 0;
    return ret;
}