#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
struct TYPE_6__ {scalar_t__ nb_streams; int /*<<< orphan*/ * streams; int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_5__ {int samples; int header_pos; } ;
typedef  TYPE_1__ MPCContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVINDEX_KEYFRAME ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int INT_MAX ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int TAG_SEEKTABLE ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  av_add_index_entry (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_malloc (scalar_t__) ; 
 int avio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int gb_get_v (int /*<<< orphan*/ *) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_unary (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mpc8_get_chunk_header (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void mpc8_parse_seektable(AVFormatContext *s, int64_t off)
{
    MPCContext *c = s->priv_data;
    int tag;
    int64_t size, pos, ppos[2];
    uint8_t *buf;
    int i, t, seekd, ret;
    GetBitContext gb;

    if (s->nb_streams == 0) {
        av_log(s, AV_LOG_ERROR, "No stream added before parsing seek table\n");
        return;
    }

    avio_seek(s->pb, off, SEEK_SET);
    mpc8_get_chunk_header(s->pb, &tag, &size);
    if(tag != TAG_SEEKTABLE){
        av_log(s, AV_LOG_ERROR, "No seek table at given position\n");
        return;
    }
    if (size > INT_MAX/10 || size<=0) {
        av_log(s, AV_LOG_ERROR, "Bad seek table size\n");
        return;
    }
    if(!(buf = av_malloc(size + AV_INPUT_BUFFER_PADDING_SIZE)))
        return;
    ret = avio_read(s->pb, buf, size);
    if (ret != size) {
        av_log(s, AV_LOG_ERROR, "seek table truncated\n");
        av_free(buf);
        return;
    }
    memset(buf+size, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    init_get_bits(&gb, buf, size * 8);
    size = gb_get_v(&gb);
    if(size > UINT_MAX/4 || size > c->samples/1152){
        av_log(s, AV_LOG_ERROR, "Seek table is too big\n");
        av_free(buf);
        return;
    }
    seekd = get_bits(&gb, 4);
    for(i = 0; i < 2; i++){
        pos = gb_get_v(&gb) + c->header_pos;
        ppos[1 - i] = pos;
        av_add_index_entry(s->streams[0], pos, i, 0, 0, AVINDEX_KEYFRAME);
    }
    for(; i < size; i++){
        t = get_unary(&gb, 1, 33) << 12;
        t += get_bits(&gb, 12);
        if(t & 1)
            t = -(t & ~1);
        pos = (t >> 1) + ppos[0]*2 - ppos[1];
        av_add_index_entry(s->streams[0], pos, i << seekd, 0, 0, AVINDEX_KEYFRAME);
        ppos[1] = ppos[0];
        ppos[0] = pos;
    }
    av_free(buf);
}