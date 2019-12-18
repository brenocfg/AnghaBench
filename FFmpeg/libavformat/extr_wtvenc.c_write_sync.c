#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  last_chunk_pos; int /*<<< orphan*/  serial; int /*<<< orphan*/  nb_sp_pairs; int /*<<< orphan*/  sp_pairs; int /*<<< orphan*/  last_timestamp_pos; int /*<<< orphan*/  first_index_pos; } ;
typedef  TYPE_1__ WtvContext ;
struct TYPE_7__ {TYPE_1__* priv_data; int /*<<< orphan*/ * pb; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  add_serial_pair (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_sync_guid ; 
 int /*<<< orphan*/  finish_chunk (TYPE_2__*) ; 
 int /*<<< orphan*/  write_chunk_header (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_sync(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    WtvContext *wctx = s->priv_data;
    int64_t last_chunk_pos = wctx->last_chunk_pos;

    write_chunk_header(s, &ff_sync_guid, 0x18, 0);
    avio_wl64(pb, wctx->first_index_pos);
    avio_wl64(pb, wctx->last_timestamp_pos);
    avio_wl64(pb, 0);

    finish_chunk(s);
    add_serial_pair(&wctx->sp_pairs, &wctx->nb_sp_pairs, wctx->serial, wctx->last_chunk_pos);

    wctx->last_chunk_pos = last_chunk_pos;
}