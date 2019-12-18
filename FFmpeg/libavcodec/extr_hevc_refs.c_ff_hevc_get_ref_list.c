#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* pps; TYPE_3__* sps; } ;
struct TYPE_12__ {TYPE_2__ ps; } ;
struct TYPE_11__ {scalar_t__* rpl_tab; } ;
struct TYPE_10__ {int log2_ctb_size; int ctb_width; } ;
struct TYPE_8__ {int* ctb_addr_rs_to_ts; } ;
typedef  int /*<<< orphan*/  RefPicList ;
typedef  TYPE_4__ HEVCFrame ;
typedef  TYPE_5__ HEVCContext ;

/* Variables and functions */

RefPicList *ff_hevc_get_ref_list(HEVCContext *s, HEVCFrame *ref, int x0, int y0)
{
    int x_cb         = x0 >> s->ps.sps->log2_ctb_size;
    int y_cb         = y0 >> s->ps.sps->log2_ctb_size;
    int pic_width_cb = s->ps.sps->ctb_width;
    int ctb_addr_ts  = s->ps.pps->ctb_addr_rs_to_ts[y_cb * pic_width_cb + x_cb];
    return (RefPicList *)ref->rpl_tab[ctb_addr_ts];
}