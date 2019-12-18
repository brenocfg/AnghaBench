#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int mode; int* ref_used; TYPE_3__** ref; int /*<<< orphan*/  out_list; int /*<<< orphan*/  frames; int /*<<< orphan*/  comb_none; int /*<<< orphan*/  comb_light; int /*<<< orphan*/  comb_heavy; } ;
typedef  TYPE_2__ hb_filter_private_t ;
struct TYPE_11__ {int combed; } ;
struct TYPE_13__ {TYPE_1__ s; } ;
typedef  TYPE_3__ hb_buffer_t ;

/* Variables and functions */
#define  HB_COMB_HEAVY 130 
#define  HB_COMB_LIGHT 129 
#define  HB_COMB_NONE 128 
 int MODE_MASK ; 
 int /*<<< orphan*/  apply_mask (TYPE_2__*,TYPE_3__*) ; 
 int comb_segmenter (TYPE_2__*) ; 
 TYPE_3__* hb_buffer_dup (TYPE_3__*) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void process_frame( hb_filter_private_t * pv )
{
    int combed;

    combed = comb_segmenter(pv);
    switch (combed)
    {
        case HB_COMB_HEAVY:
            pv->comb_heavy++;
            break;

        case HB_COMB_LIGHT:
            pv->comb_light++;
            break;

        case HB_COMB_NONE:
        default:
            pv->comb_none++;
            break;
    }
    pv->frames++;
    if ((pv->mode & MODE_MASK) && combed)
    {
        hb_buffer_t * out;
        out = hb_buffer_dup(pv->ref[1]);
        apply_mask(pv, out);
        out->s.combed = combed;
        hb_buffer_list_append(&pv->out_list, out);
    }
    else
    {
        pv->ref_used[1] = 1;
        pv->ref[1]->s.combed = combed;
        hb_buffer_list_append(&pv->out_list, pv->ref[1]);
    }
}