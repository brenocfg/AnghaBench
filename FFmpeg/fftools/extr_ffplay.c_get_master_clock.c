#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  extclk; int /*<<< orphan*/  audclk; int /*<<< orphan*/  vidclk; } ;
typedef  TYPE_1__ VideoState ;

/* Variables and functions */
#define  AV_SYNC_AUDIO_MASTER 129 
#define  AV_SYNC_VIDEO_MASTER 128 
 double get_clock (int /*<<< orphan*/ *) ; 
 int get_master_sync_type (TYPE_1__*) ; 

__attribute__((used)) static double get_master_clock(VideoState *is)
{
    double val;

    switch (get_master_sync_type(is)) {
        case AV_SYNC_VIDEO_MASTER:
            val = get_clock(&is->vidclk);
            break;
        case AV_SYNC_AUDIO_MASTER:
            val = get_clock(&is->audclk);
            break;
        default:
            val = get_clock(&is->extclk);
            break;
    }
    return val;
}