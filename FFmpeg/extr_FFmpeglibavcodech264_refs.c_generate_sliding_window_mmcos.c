#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* sps; } ;
struct TYPE_14__ {int short_ref_count; scalar_t__ long_ref_count; int nb_mmco; TYPE_4__** short_ref; TYPE_3__* cur_pic_ptr; int /*<<< orphan*/  first_field; TYPE_2__ ps; TYPE_5__* mmco; } ;
struct TYPE_13__ {int short_pic_num; void* opcode; } ;
struct TYPE_12__ {int frame_num; } ;
struct TYPE_11__ {scalar_t__ reference; } ;
struct TYPE_9__ {scalar_t__ ref_frame_count; } ;
typedef  TYPE_5__ MMCO ;
typedef  TYPE_6__ H264Context ;

/* Variables and functions */
 scalar_t__ FIELD_PICTURE (TYPE_6__*) ; 
 void* MMCO_SHORT2UNUSED ; 

__attribute__((used)) static void generate_sliding_window_mmcos(H264Context *h)
{
    MMCO *mmco = h->mmco;
    int nb_mmco = 0;

    if (h->short_ref_count &&
        h->long_ref_count + h->short_ref_count >= h->ps.sps->ref_frame_count &&
        !(FIELD_PICTURE(h) && !h->first_field && h->cur_pic_ptr->reference)) {
        mmco[0].opcode        = MMCO_SHORT2UNUSED;
        mmco[0].short_pic_num = h->short_ref[h->short_ref_count - 1]->frame_num;
        nb_mmco               = 1;
        if (FIELD_PICTURE(h)) {
            mmco[0].short_pic_num *= 2;
            mmco[1].opcode         = MMCO_SHORT2UNUSED;
            mmco[1].short_pic_num  = mmco[0].short_pic_num + 1;
            nb_mmco                = 2;
        }
    }

    h->nb_mmco = nb_mmco;
}