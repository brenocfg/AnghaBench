#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t nb_streams; TYPE_2__** streams; TYPE_1__* priv_data; } ;
struct TYPE_7__ {scalar_t__ discard; } ;
struct TYPE_6__ {size_t curr_stream; } ;
typedef  TYPE_1__ AviSynthContext ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVDISCARD_ALL ; 

__attribute__((used)) static void avisynth_next_stream(AVFormatContext *s, AVStream **st,
                                 AVPacket *pkt, int *discard)
{
    AviSynthContext *avs = s->priv_data;

    avs->curr_stream++;
    avs->curr_stream %= s->nb_streams;

    *st = s->streams[avs->curr_stream];
    if ((*st)->discard == AVDISCARD_ALL)
        *discard = 1;
    else
        *discard = 0;

    return;
}