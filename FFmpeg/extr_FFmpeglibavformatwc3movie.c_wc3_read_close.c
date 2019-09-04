#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ size; } ;
struct TYPE_5__ {TYPE_4__ vpkt; } ;
typedef  TYPE_1__ Wc3DemuxContext ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_packet_unref (TYPE_4__*) ; 

__attribute__((used)) static int wc3_read_close(AVFormatContext *s)
{
    Wc3DemuxContext *wc3 = s->priv_data;

    if (wc3->vpkt.size > 0)
        av_packet_unref(&wc3->vpkt);

    return 0;
}