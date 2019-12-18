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
struct TYPE_6__ {int disposition; int /*<<< orphan*/  time_base; } ;
struct TYPE_5__ {scalar_t__ nb_packets; double duration; scalar_t__ abort_request; } ;
typedef  TYPE_1__ PacketQueue ;
typedef  TYPE_2__ AVStream ;

/* Variables and functions */
 int AV_DISPOSITION_ATTACHED_PIC ; 
 scalar_t__ MIN_FRAMES ; 
 double av_q2d (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stream_has_enough_packets(AVStream *st, int stream_id, PacketQueue *queue) {
    return stream_id < 0 ||
           queue->abort_request ||
           (st->disposition & AV_DISPOSITION_ATTACHED_PIC) ||
           queue->nb_packets > MIN_FRAMES && (!queue->duration || av_q2d(st->time_base) * queue->duration > 1.0);
}