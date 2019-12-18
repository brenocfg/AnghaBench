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
struct TYPE_5__ {int size; scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  album_peak; int /*<<< orphan*/  album_gain; int /*<<< orphan*/  track_peak; int /*<<< orphan*/  track_gain; } ;
typedef  TYPE_1__ AVReplayGain ;
typedef  TYPE_2__ AVPacketSideData ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_gain (void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_peak (void*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_replaygain(void *ctx, AVPacketSideData *sd)
{
    AVReplayGain *rg;

    if (sd->size < sizeof(*rg)) {
        av_log(ctx, AV_LOG_ERROR, "invalid data");
        return;
    }
    rg = (AVReplayGain*)sd->data;

    print_gain(ctx, "track gain", rg->track_gain);
    print_peak(ctx, "track peak", rg->track_peak);
    print_gain(ctx, "album gain", rg->album_gain);
    print_peak(ctx, "album peak", rg->album_peak);
}