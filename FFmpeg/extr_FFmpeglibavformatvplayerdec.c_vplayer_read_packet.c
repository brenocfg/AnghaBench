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
struct TYPE_4__ {int /*<<< orphan*/  q; } ;
typedef  TYPE_1__ VPlayerContext ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int ff_subtitles_queue_read_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vplayer_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    VPlayerContext *vplayer = s->priv_data;
    return ff_subtitles_queue_read_packet(&vplayer->q, pkt);
}