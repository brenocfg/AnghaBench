#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ size; } ;
struct TYPE_9__ {int nb_streams; TYPE_2__** streams; TYPE_1__* internal; } ;
struct TYPE_8__ {int disposition; scalar_t__ discard; TYPE_4__ attached_pic; } ;
struct TYPE_7__ {int /*<<< orphan*/  raw_packet_buffer_end; int /*<<< orphan*/  raw_packet_buffer; } ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVDISCARD_ALL ; 
 int AV_DISPOSITION_ATTACHED_PIC ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  FF_PACKETLIST_FLAG_REF_PACKET ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int ff_packet_list_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 

int avformat_queue_attached_pictures(AVFormatContext *s)
{
    int i, ret;
    for (i = 0; i < s->nb_streams; i++)
        if (s->streams[i]->disposition & AV_DISPOSITION_ATTACHED_PIC &&
            s->streams[i]->discard < AVDISCARD_ALL) {
            if (s->streams[i]->attached_pic.size <= 0) {
                av_log(s, AV_LOG_WARNING,
                    "Attached picture on stream %d has invalid size, "
                    "ignoring\n", i);
                continue;
            }

            ret = ff_packet_list_put(&s->internal->raw_packet_buffer,
                                     &s->internal->raw_packet_buffer_end,
                                     &s->streams[i]->attached_pic,
                                     FF_PACKETLIST_FLAG_REF_PACKET);
            if (ret < 0)
                return ret;
        }
    return 0;
}