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
struct TYPE_9__ {TYPE_4__* priv_data; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_11__ {int nb_tracked_methods; TYPE_1__* tracked_methods; } ;
struct TYPE_10__ {scalar_t__ size; scalar_t__ data; } ;
struct TYPE_8__ {double id; char* name; } ;
typedef  TYPE_3__ RTMPPacket ;
typedef  TYPE_4__ RTMPContext ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  del_tracked_method (TYPE_4__*,int) ; 
 int ff_amf_read_number (int /*<<< orphan*/ *,double*) ; 

__attribute__((used)) static int find_tracked_method(URLContext *s, RTMPPacket *pkt, int offset,
                               char **tracked_method)
{
    RTMPContext *rt = s->priv_data;
    GetByteContext gbc;
    double pkt_id;
    int ret;
    int i;

    bytestream2_init(&gbc, pkt->data + offset, pkt->size - offset);
    if ((ret = ff_amf_read_number(&gbc, &pkt_id)) < 0)
        return ret;

    for (i = 0; i < rt->nb_tracked_methods; i++) {
        if (rt->tracked_methods[i].id != pkt_id)
            continue;

        *tracked_method = rt->tracked_methods[i].name;
        del_tracked_method(rt, i);
        break;
    }

    return 0;
}