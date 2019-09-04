#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * ms_mask; TYPE_2__* ch; } ;
struct TYPE_5__ {int num_window_groups; int max_sfb; } ;
struct TYPE_6__ {TYPE_1__ ics; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ ChannelElement ;

/* Variables and functions */
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void decode_mid_side_stereo(ChannelElement *cpe, GetBitContext *gb,
                                   int ms_present)
{
    int idx;
    int max_idx = cpe->ch[0].ics.num_window_groups * cpe->ch[0].ics.max_sfb;
    if (ms_present == 1) {
        for (idx = 0; idx < max_idx; idx++)
            cpe->ms_mask[idx] = get_bits1(gb);
    } else if (ms_present == 2) {
        memset(cpe->ms_mask, 1, max_idx * sizeof(cpe->ms_mask[0]));
    }
}