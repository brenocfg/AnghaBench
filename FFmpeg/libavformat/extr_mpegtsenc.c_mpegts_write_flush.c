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
struct TYPE_9__ {int nb_streams; TYPE_2__** streams; } ;
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {scalar_t__ payload_size; int payload_flags; scalar_t__ opus_queued_samples; int /*<<< orphan*/  payload_dts; int /*<<< orphan*/  payload_pts; int /*<<< orphan*/  payload; } ;
typedef  TYPE_1__ MpegTSWriteStream ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  mpegts_write_pes (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void mpegts_write_flush(AVFormatContext *s)
{
    int i;

    /* flush current packets */
    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];
        MpegTSWriteStream *ts_st = st->priv_data;
        if (ts_st->payload_size > 0) {
            mpegts_write_pes(s, st, ts_st->payload, ts_st->payload_size,
                             ts_st->payload_pts, ts_st->payload_dts,
                             ts_st->payload_flags & AV_PKT_FLAG_KEY, -1);
            ts_st->payload_size = 0;
            ts_st->opus_queued_samples = 0;
        }
    }
}