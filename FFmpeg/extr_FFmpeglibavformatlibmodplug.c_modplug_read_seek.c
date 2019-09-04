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
typedef  int int64_t ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int packet_count; int ts_per_packet; scalar_t__ video_stream; int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ ModPlugContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  ModPlug_Seek (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int modplug_read_seek(AVFormatContext *s, int stream_idx, int64_t ts, int flags)
{
    ModPlugContext *modplug = s->priv_data;
    ModPlug_Seek(modplug->f, (int)ts);
    if (modplug->video_stream)
        modplug->packet_count = ts / modplug->ts_per_packet;
    return 0;
}