#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  duration; int /*<<< orphan*/  metadata; } ;
struct TYPE_5__ {int time_scale; void*** movie_display_matrix; void* duration; TYPE_3__* fc; int /*<<< orphan*/  trex_data; } ;
typedef  TYPE_1__ MOVContext ;
typedef  int /*<<< orphan*/  MOVAtom ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  AV_TIME_BASE ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  av_rescale (void*,int /*<<< orphan*/ ,int) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb24 (int /*<<< orphan*/ *) ; 
 void* avio_rb32 (int /*<<< orphan*/ *) ; 
 void* avio_rb64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mov_metadata_creation_time (int /*<<< orphan*/ *,void*,TYPE_3__*) ; 

__attribute__((used)) static int mov_read_mvhd(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    int i;
    int64_t creation_time;
    int version = avio_r8(pb); /* version */
    avio_rb24(pb); /* flags */

    if (version == 1) {
        creation_time = avio_rb64(pb);
        avio_rb64(pb);
    } else {
        creation_time = avio_rb32(pb);
        avio_rb32(pb); /* modification time */
    }
    mov_metadata_creation_time(&c->fc->metadata, creation_time, c->fc);
    c->time_scale = avio_rb32(pb); /* time scale */
    if (c->time_scale <= 0) {
        av_log(c->fc, AV_LOG_ERROR, "Invalid mvhd time scale %d, defaulting to 1\n", c->time_scale);
        c->time_scale = 1;
    }
    av_log(c->fc, AV_LOG_TRACE, "time scale = %i\n", c->time_scale);

    c->duration = (version == 1) ? avio_rb64(pb) : avio_rb32(pb); /* duration */
    // set the AVCodecContext duration because the duration of individual tracks
    // may be inaccurate
    if (c->time_scale > 0 && !c->trex_data)
        c->fc->duration = av_rescale(c->duration, AV_TIME_BASE, c->time_scale);
    avio_rb32(pb); /* preferred scale */

    avio_rb16(pb); /* preferred volume */

    avio_skip(pb, 10); /* reserved */

    /* movie display matrix, store it in main context and use it later on */
    for (i = 0; i < 3; i++) {
        c->movie_display_matrix[i][0] = avio_rb32(pb); // 16.16 fixed point
        c->movie_display_matrix[i][1] = avio_rb32(pb); // 16.16 fixed point
        c->movie_display_matrix[i][2] = avio_rb32(pb); //  2.30 fixed point
    }

    avio_rb32(pb); /* preview time */
    avio_rb32(pb); /* preview duration */
    avio_rb32(pb); /* poster time */
    avio_rb32(pb); /* selection time */
    avio_rb32(pb); /* selection duration */
    avio_rb32(pb); /* current time */
    avio_rb32(pb); /* next track ID */

    return 0;
}