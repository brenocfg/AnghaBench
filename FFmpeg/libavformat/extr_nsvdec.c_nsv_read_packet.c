#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * data; } ;
struct TYPE_11__ {TYPE_1__* priv_data; } ;
struct TYPE_10__ {int size; } ;
struct TYPE_9__ {TYPE_8__* ahead; } ;
typedef  TYPE_1__ NSVContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_8__*,int) ; 
 int nsv_read_chunk (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nsv_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    NSVContext *nsv = s->priv_data;
    int i, err = 0;

    /* in case we don't already have something to eat ... */
    if (!nsv->ahead[0].data && !nsv->ahead[1].data)
        err = nsv_read_chunk(s, 0);
    if (err < 0)
        return err;

    /* now pick one of the plates */
    for (i = 0; i < 2; i++) {
        if (nsv->ahead[i].data) {
            /* avoid the cost of new_packet + memcpy(->data) */
            memcpy(pkt, &nsv->ahead[i], sizeof(AVPacket));
            nsv->ahead[i].data = NULL; /* we ate that one */
            return pkt->size;
        }
    }

    /* this restaurant is not provisioned :^] */
    return -1;
}