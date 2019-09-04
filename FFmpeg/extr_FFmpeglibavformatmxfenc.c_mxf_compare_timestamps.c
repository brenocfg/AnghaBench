#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__** streams; } ;
struct TYPE_10__ {size_t stream_index; scalar_t__ dts; } ;
struct TYPE_9__ {scalar_t__ order; } ;
struct TYPE_8__ {TYPE_2__* priv_data; } ;
typedef  TYPE_2__ MXFStreamContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */

__attribute__((used)) static int mxf_compare_timestamps(AVFormatContext *s, AVPacket *next, AVPacket *pkt)
{
    MXFStreamContext *sc  = s->streams[pkt ->stream_index]->priv_data;
    MXFStreamContext *sc2 = s->streams[next->stream_index]->priv_data;

    return next->dts > pkt->dts ||
        (next->dts == pkt->dts && sc->order < sc2->order);
}