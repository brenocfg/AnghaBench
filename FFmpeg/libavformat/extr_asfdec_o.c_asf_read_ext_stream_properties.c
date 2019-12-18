#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ff_asf_guid ;
struct TYPE_19__ {int nb_streams; int /*<<< orphan*/  offset; TYPE_1__** asf_st; } ;
struct TYPE_18__ {TYPE_5__** streams; int /*<<< orphan*/ * pb; TYPE_7__* priv_data; } ;
struct TYPE_15__ {int num; void* den; } ;
struct TYPE_17__ {TYPE_3__ avg_frame_rate; TYPE_2__* codecpar; void* duration; void* start_time; } ;
struct TYPE_16__ {int (* read_object ) (TYPE_6__*,TYPE_4__ const*) ;int /*<<< orphan*/  name; } ;
struct TYPE_14__ {int bit_rate; } ;
struct TYPE_13__ {int stream_index; size_t index; int lang_idx; } ;
typedef  TYPE_4__ GUIDParseTable ;
typedef  TYPE_5__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_6__ AVFormatContext ;
typedef  TYPE_7__ ASFContext ;

/* Variables and functions */
 int ASF_STREAM_NUM ; 
 int /*<<< orphan*/  align_position (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int avio_rl32 (int /*<<< orphan*/ *) ; 
 void* avio_rl64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int ff_get_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* find_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int stub1 (TYPE_6__*,TYPE_4__ const*) ; 

__attribute__((used)) static int asf_read_ext_stream_properties(AVFormatContext *s, const GUIDParseTable *g)
{
    ASFContext *asf = s->priv_data;
    AVIOContext *pb = s->pb;
    AVStream *st    = NULL;
    ff_asf_guid guid;
    uint16_t nb_st_name, nb_pay_exts, st_num, lang_idx;
    int i, ret;
    uint32_t bitrate;
    uint64_t start_time, end_time, time_per_frame;
    uint64_t size = avio_rl64(pb);

    start_time = avio_rl64(pb);
    end_time   = avio_rl64(pb);
    bitrate    = avio_rl32(pb);
    avio_skip(pb, 28); // skip some unused values
    st_num     = avio_rl16(pb);
    st_num    &= ASF_STREAM_NUM;
    lang_idx   = avio_rl16(pb); // Stream Language ID Index
    for (i = 0; i < asf->nb_streams; i++) {
        if (st_num == asf->asf_st[i]->stream_index) {
            st                       = s->streams[asf->asf_st[i]->index];
            asf->asf_st[i]->lang_idx = lang_idx;
            break;
        }
    }
    time_per_frame = avio_rl64(pb); // average time per frame
    if (st) {
        st->start_time           = start_time;
        st->duration             = end_time - start_time;
        st->codecpar->bit_rate   = bitrate;
        st->avg_frame_rate.num   = 10000000;
        st->avg_frame_rate.den   = time_per_frame;
    }
    nb_st_name = avio_rl16(pb);
    nb_pay_exts   = avio_rl16(pb);
    for (i = 0; i < nb_st_name; i++) {
        uint16_t len;

        avio_rl16(pb); // Language ID Index
        len = avio_rl16(pb);
        avio_skip(pb, len);
    }

    for (i = 0; i < nb_pay_exts; i++) {
        uint32_t len;
        avio_skip(pb, 16); // Extension System ID
        avio_skip(pb, 2);  // Extension Data Size
        len = avio_rl32(pb);
        avio_skip(pb, len);
    }

    if ((ret = ff_get_guid(pb, &guid)) < 0) {
        align_position(pb, asf->offset, size);

        return 0;
    }

    g = find_guid(guid);
    if (g && !(strcmp(g->name, "Stream Properties"))) {
        if ((ret = g->read_object(s, g)) < 0)
            return ret;
    }

    align_position(pb, asf->offset, size);
    return 0;
}