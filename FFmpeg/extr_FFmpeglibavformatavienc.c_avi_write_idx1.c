#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_23__ {int nb_streams; TYPE_2__** streams; TYPE_6__* priv_data; TYPE_4__* pb; } ;
struct TYPE_22__ {int /*<<< orphan*/  riff_id; } ;
struct TYPE_21__ {scalar_t__ pos; char* tag; scalar_t__ flags; scalar_t__ len; } ;
struct TYPE_20__ {int seekable; } ;
struct TYPE_16__ {scalar_t__ entry; } ;
struct TYPE_19__ {scalar_t__ entry; TYPE_15__ indexes; } ;
struct TYPE_18__ {TYPE_1__* codecpar; TYPE_3__* priv_data; } ;
struct TYPE_17__ {int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_3__ AVIStream ;
typedef  TYPE_4__ AVIOContext ;
typedef  TYPE_5__ AVIIentry ;
typedef  TYPE_6__ AVIContext ;
typedef  TYPE_7__ AVFormatContext ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 TYPE_5__* avi_get_ientry (TYPE_15__*,scalar_t__) ; 
 int /*<<< orphan*/  avi_stream2fourcc (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avi_write_counters (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl32 (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  ff_end_tag (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_start_tag (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  ffio_wfourcc (TYPE_4__*,char*) ; 

__attribute__((used)) static int avi_write_idx1(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    AVIContext *avi = s->priv_data;
    int64_t idx_chunk;
    int i;
    char tag[5];

    if (pb->seekable & AVIO_SEEKABLE_NORMAL) {
        AVIStream *avist;
        AVIIentry *ie = 0, *tie;
        int empty, stream_id = -1;

        idx_chunk = ff_start_tag(pb, "idx1");
        for (i = 0; i < s->nb_streams; i++) {
            avist        = s->streams[i]->priv_data;
            avist->entry = 0;
        }

        do {
            empty = 1;
            for (i = 0; i < s->nb_streams; i++) {
                avist = s->streams[i]->priv_data;
                if (avist->indexes.entry <= avist->entry)
                    continue;

                tie = avi_get_ientry(&avist->indexes, avist->entry);
                if (empty || tie->pos < ie->pos) {
                    ie        = tie;
                    stream_id = i;
                }
                empty = 0;
            }
            if (!empty) {
                avist = s->streams[stream_id]->priv_data;
                if (*ie->tag)
                    ffio_wfourcc(pb, ie->tag);
                else {
                    avi_stream2fourcc(tag, stream_id,
                                  s->streams[stream_id]->codecpar->codec_type);
                    ffio_wfourcc(pb, tag);
                }
                avio_wl32(pb, ie->flags);
                avio_wl32(pb, ie->pos);
                avio_wl32(pb, ie->len);
                avist->entry++;
            }
        } while (!empty);
        ff_end_tag(pb, idx_chunk);

        avi_write_counters(s, avi->riff_id);
    }
    return 0;
}