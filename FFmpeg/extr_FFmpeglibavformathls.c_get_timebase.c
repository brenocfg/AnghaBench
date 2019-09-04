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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t stream_index; } ;
struct playlist {TYPE_3__ pkt; TYPE_2__* ctx; scalar_t__ is_id3_timestamped; } ;
struct TYPE_5__ {TYPE_1__** streams; } ;
struct TYPE_4__ {int /*<<< orphan*/  time_base; } ;
typedef  int /*<<< orphan*/  AVRational ;

/* Variables and functions */
 int /*<<< orphan*/  MPEG_TIME_BASE_Q ; 

__attribute__((used)) static AVRational get_timebase(struct playlist *pls)
{
    if (pls->is_id3_timestamped)
        return MPEG_TIME_BASE_Q;

    return pls->ctx->streams[pls->pkt.stream_index]->time_base;
}