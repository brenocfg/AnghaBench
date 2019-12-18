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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {TYPE_1__* priv_data; int /*<<< orphan*/ * pb; } ;
struct TYPE_6__ {int resync_size; } ;
typedef  TYPE_1__ MpegTSContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reanalyze (TYPE_1__*) ; 

__attribute__((used)) static int mpegts_resync(AVFormatContext *s, int seekback, const uint8_t *current_packet)
{
    MpegTSContext *ts = s->priv_data;
    AVIOContext *pb = s->pb;
    int c, i;
    uint64_t pos = avio_tell(pb);

    avio_seek(pb, -FFMIN(seekback, pos), SEEK_CUR);

    //Special case for files like 01c56b0dc1.ts
    if (current_packet[0] == 0x80 && current_packet[12] == 0x47) {
        avio_seek(pb, 12, SEEK_CUR);
        return 0;
    }

    for (i = 0; i < ts->resync_size; i++) {
        c = avio_r8(pb);
        if (avio_feof(pb))
            return AVERROR_EOF;
        if (c == 0x47) {
            avio_seek(pb, -1, SEEK_CUR);
            reanalyze(s->priv_data);
            return 0;
        }
    }
    av_log(s, AV_LOG_ERROR,
           "max resync size reached, could not find sync byte\n");
    /* no sync found */
    return AVERROR_INVALIDDATA;
}