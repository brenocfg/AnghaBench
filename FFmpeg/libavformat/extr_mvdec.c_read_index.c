#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int nb_frames; TYPE_1__* codecpar; } ;
struct TYPE_5__ {scalar_t__ codec_type; int channels; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVINDEX_KEYFRAME ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  av_add_index_entry (TYPE_2__*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void read_index(AVIOContext *pb, AVStream *st)
{
    uint64_t timestamp = 0;
    int i;
    for (i = 0; i < st->nb_frames; i++) {
        uint32_t pos  = avio_rb32(pb);
        uint32_t size = avio_rb32(pb);
        avio_skip(pb, 8);
        av_add_index_entry(st, pos, timestamp, size, 0, AVINDEX_KEYFRAME);
        if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            timestamp += size / (st->codecpar->channels * 2);
        } else {
            timestamp++;
        }
    }
}