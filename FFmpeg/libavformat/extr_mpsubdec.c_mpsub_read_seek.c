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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  q; } ;
typedef  TYPE_1__ MPSubContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int ff_subtitles_queue_seek (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mpsub_read_seek(AVFormatContext *s, int stream_index,
                           int64_t min_ts, int64_t ts, int64_t max_ts, int flags)
{
    MPSubContext *mpsub = s->priv_data;
    return ff_subtitles_queue_seek(&mpsub->q, s, stream_index,
                                   min_ts, ts, max_ts, flags);
}