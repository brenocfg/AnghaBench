#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ff_asf_guid ;
struct TYPE_5__ {int nb_index; int /*<<< orphan*/  serial; scalar_t__ last_chunk_pos; TYPE_2__* index; scalar_t__ timeline_start_pos; } ;
typedef  TYPE_1__ WtvContext ;
struct TYPE_6__ {int stream_id; int /*<<< orphan*/  const* guid; int /*<<< orphan*/  serial; scalar_t__ pos; } ;
typedef  TYPE_2__ WtvChunkEntry ;
struct TYPE_7__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ MAX_NB_INDEX ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const ff_index_guid ; 
 int /*<<< orphan*/  ff_put_guid (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void write_chunk_header(AVFormatContext *s, const ff_asf_guid *guid, int length, int stream_id)
{
    WtvContext *wctx = s->priv_data;
    AVIOContext *pb = s->pb;

    wctx->last_chunk_pos = avio_tell(pb) - wctx->timeline_start_pos;
    ff_put_guid(pb, guid);
    avio_wl32(pb, 32 + length);
    avio_wl32(pb, stream_id);
    avio_wl64(pb, wctx->serial);

    if ((stream_id & 0x80000000) && guid != &ff_index_guid) {
        WtvChunkEntry *t = wctx->index + wctx->nb_index;
        av_assert0(wctx->nb_index < MAX_NB_INDEX);
        t->pos       = wctx->last_chunk_pos;
        t->serial    = wctx->serial;
        t->guid      = guid;
        t->stream_id = stream_id & 0x3FFFFFFF;
        wctx->nb_index++;
    }
}