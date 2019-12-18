#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* sps; } ;
struct TYPE_9__ {int /*<<< orphan*/  skip_flag; TYPE_3__* HEVClc; TYPE_2__ ps; } ;
struct TYPE_8__ {scalar_t__ ctb_up_flag; scalar_t__ ctb_left_flag; } ;
struct TYPE_6__ {int min_cb_width; int /*<<< orphan*/  log2_ctb_size; } ;
typedef  TYPE_4__ HEVCContext ;

/* Variables and functions */
 int GET_CABAC (scalar_t__) ; 
 int /*<<< orphan*/  SAMPLE_CTB (int /*<<< orphan*/ ,int,int) ; 
 size_t SKIP_FLAG ; 
 int av_mod_uintp2 (int,int /*<<< orphan*/ ) ; 
 scalar_t__* elem_offset ; 

int ff_hevc_skip_flag_decode(HEVCContext *s, int x0, int y0, int x_cb, int y_cb)
{
    int min_cb_width = s->ps.sps->min_cb_width;
    int inc = 0;
    int x0b = av_mod_uintp2(x0, s->ps.sps->log2_ctb_size);
    int y0b = av_mod_uintp2(y0, s->ps.sps->log2_ctb_size);

    if (s->HEVClc->ctb_left_flag || x0b)
        inc = !!SAMPLE_CTB(s->skip_flag, x_cb - 1, y_cb);
    if (s->HEVClc->ctb_up_flag || y0b)
        inc += !!SAMPLE_CTB(s->skip_flag, x_cb, y_cb - 1);

    return GET_CABAC(elem_offset[SKIP_FLAG] + inc);
}