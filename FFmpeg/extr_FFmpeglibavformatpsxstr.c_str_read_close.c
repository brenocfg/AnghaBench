#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ data; } ;
struct TYPE_8__ {TYPE_2__* priv_data; } ;
struct TYPE_7__ {TYPE_1__* channels; } ;
struct TYPE_6__ {TYPE_5__ tmp_pkt; } ;
typedef  TYPE_2__ StrDemuxContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_packet_unref (TYPE_5__*) ; 

__attribute__((used)) static int str_read_close(AVFormatContext *s)
{
    StrDemuxContext *str = s->priv_data;
    int i;
    for(i=0; i<32; i++){
        if(str->channels[i].tmp_pkt.data)
            av_packet_unref(&str->channels[i].tmp_pkt);
    }

    return 0;
}