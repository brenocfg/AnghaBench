#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_4__ {int last_chunk_pos; int timeline_start_pos; int /*<<< orphan*/  serial; } ;
typedef  TYPE_1__ WtvContext ;
struct TYPE_5__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ WTV_PAD8 (int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_pad (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void finish_chunk_noindex(AVFormatContext *s)
{
    WtvContext *wctx = s->priv_data;
    AVIOContext *pb = s->pb;

    // update the chunk_len field and pad.
    int64_t chunk_len = avio_tell(pb) - (wctx->last_chunk_pos + wctx->timeline_start_pos);
    avio_seek(pb, -(chunk_len - 16), SEEK_CUR);
    avio_wl32(pb, chunk_len);
    avio_seek(pb, chunk_len - (16 + 4), SEEK_CUR);

    write_pad(pb, WTV_PAD8(chunk_len) - chunk_len);
    wctx->serial++;
}