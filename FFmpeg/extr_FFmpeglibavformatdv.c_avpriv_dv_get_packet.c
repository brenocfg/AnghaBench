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
struct TYPE_6__ {int size; } ;
struct TYPE_5__ {int ach; TYPE_2__* audio_pkt; scalar_t__* ast; } ;
typedef  TYPE_1__ DVDemuxContext ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */

int avpriv_dv_get_packet(DVDemuxContext *c, AVPacket *pkt)
{
    int size = -1;
    int i;

    for (i = 0; i < c->ach; i++) {
        if (c->ast[i] && c->audio_pkt[i].size) {
            *pkt                 = c->audio_pkt[i];
            c->audio_pkt[i].size = 0;
            size                 = pkt->size;
            break;
        }
    }

    return size;
}