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
struct TYPE_6__ {int nb_st_pairs; int /*<<< orphan*/  last_serial; int /*<<< orphan*/  last_pts; TYPE_1__* st_pairs; } ;
typedef  TYPE_2__ WtvContext ;
struct TYPE_7__ {TYPE_2__* priv_data; int /*<<< orphan*/ * pb; } ;
struct TYPE_5__ {int /*<<< orphan*/  serial; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_wl64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_table_entries_time(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    WtvContext *wctx = s->priv_data;
    int i;
    for (i = 0; i < wctx->nb_st_pairs; i++) {
        avio_wl64(pb, wctx->st_pairs[i].value);
        avio_wl64(pb, wctx->st_pairs[i].serial);
    }
    avio_wl64(pb, wctx->last_pts);
    avio_wl64(pb, wctx->last_serial);
}