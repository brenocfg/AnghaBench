#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__** delayed_pic; scalar_t__ first_field; int /*<<< orphan*/ * cur_pic_ptr; } ;
struct TYPE_8__ {scalar_t__ poc; int /*<<< orphan*/  reference; int /*<<< orphan*/  mmco_reset; TYPE_1__* f; } ;
struct TYPE_7__ {int /*<<< orphan*/  key_frame; } ;
typedef  TYPE_2__ H264Picture ;
typedef  TYPE_3__ H264Context ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  DELAYED_PIC_REF ; 
 int finalize_frame (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*,int*) ; 

__attribute__((used)) static int send_next_delayed_frame(H264Context *h, AVFrame *dst_frame,
                                   int *got_frame, int buf_index)
{
    int ret, i, out_idx;
    H264Picture *out = h->delayed_pic[0];

    h->cur_pic_ptr = NULL;
    h->first_field = 0;

    out_idx = 0;
    for (i = 1;
         h->delayed_pic[i] &&
         !h->delayed_pic[i]->f->key_frame &&
         !h->delayed_pic[i]->mmco_reset;
         i++)
        if (h->delayed_pic[i]->poc < out->poc) {
            out     = h->delayed_pic[i];
            out_idx = i;
        }

    for (i = out_idx; h->delayed_pic[i]; i++)
        h->delayed_pic[i] = h->delayed_pic[i + 1];

    if (out) {
        out->reference &= ~DELAYED_PIC_REF;
        ret = finalize_frame(h, dst_frame, out, got_frame);
        if (ret < 0)
            return ret;
    }

    return buf_index;
}