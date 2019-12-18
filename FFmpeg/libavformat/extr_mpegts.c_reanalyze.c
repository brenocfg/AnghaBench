#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_4__ {scalar_t__ pos47_full; scalar_t__* size_stat; scalar_t__ size_stat_count; int raw_packet_size; TYPE_3__* stream; } ;
typedef  TYPE_1__ MpegTSContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ SIZE_STAT_THRESHOLD ; 
 scalar_t__ TS_DVHS_PACKET_SIZE ; 
 scalar_t__ TS_FEC_PACKET_SIZE ; 
 scalar_t__ TS_PACKET_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void reanalyze(MpegTSContext *ts) {
    AVIOContext *pb = ts->stream->pb;
    int64_t pos = avio_tell(pb);
    if (pos < 0)
        return;
    pos -= ts->pos47_full;
    if (pos == TS_PACKET_SIZE) {
        ts->size_stat[0] ++;
    } else if (pos == TS_DVHS_PACKET_SIZE) {
        ts->size_stat[1] ++;
    } else if (pos == TS_FEC_PACKET_SIZE) {
        ts->size_stat[2] ++;
    }

    ts->size_stat_count ++;
    if (ts->size_stat_count > SIZE_STAT_THRESHOLD) {
        int newsize = 0;
        if (ts->size_stat[0] > SIZE_STAT_THRESHOLD) {
            newsize = TS_PACKET_SIZE;
        } else if (ts->size_stat[1] > SIZE_STAT_THRESHOLD) {
            newsize = TS_DVHS_PACKET_SIZE;
        } else if (ts->size_stat[2] > SIZE_STAT_THRESHOLD) {
            newsize = TS_FEC_PACKET_SIZE;
        }
        if (newsize && newsize != ts->raw_packet_size) {
            av_log(ts->stream, AV_LOG_WARNING, "changing packet size to %d\n", newsize);
            ts->raw_packet_size = newsize;
        }
        ts->size_stat_count = 0;
        memset(ts->size_stat, 0, sizeof(ts->size_stat));
    }
}