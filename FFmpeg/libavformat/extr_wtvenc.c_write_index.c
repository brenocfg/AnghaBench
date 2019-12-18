#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nb_index; scalar_t__ last_chunk_pos; scalar_t__ first_index_pos; TYPE_2__* index; } ;
typedef  TYPE_1__ WtvContext ;
struct TYPE_8__ {int /*<<< orphan*/  serial; int /*<<< orphan*/  stream_id; int /*<<< orphan*/  pos; int /*<<< orphan*/  guid; } ;
typedef  TYPE_2__ WtvChunkEntry ;
struct TYPE_9__ {TYPE_1__* priv_data; int /*<<< orphan*/ * pb; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_index_guid ; 
 int /*<<< orphan*/  ff_put_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_chunk_noindex (TYPE_3__*) ; 
 int /*<<< orphan*/  write_chunk_header2 (TYPE_3__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void write_index(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    WtvContext *wctx = s->priv_data;
    int i;

    write_chunk_header2(s, &ff_index_guid, 0x80000000);
    avio_wl32(pb, 0);
    avio_wl32(pb, 0);

    for (i = 0; i < wctx->nb_index; i++) {
        WtvChunkEntry *t = wctx->index + i;
        ff_put_guid(pb,  t->guid);
        avio_wl64(pb, t->pos);
        avio_wl32(pb, t->stream_id);
        avio_wl32(pb, 0); // checksum?
        avio_wl64(pb, t->serial);
    }
    wctx->nb_index = 0;   // reset index
    finish_chunk_noindex(s);

    if (!wctx->first_index_pos)
        wctx->first_index_pos = wctx->last_chunk_pos;
}