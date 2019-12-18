#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  mtype; } ;
struct TYPE_4__ {int linesize; int uvlinesize; int /*<<< orphan*/ ** dest; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ H261Context ;

/* Variables and functions */
 int /*<<< orphan*/  IS_FIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h261_loop_filter (int /*<<< orphan*/ *,int const) ; 

void ff_h261_loop_filter(MpegEncContext *s)
{
    H261Context *h       = (H261Context *)s;
    const int linesize   = s->linesize;
    const int uvlinesize = s->uvlinesize;
    uint8_t *dest_y      = s->dest[0];
    uint8_t *dest_cb     = s->dest[1];
    uint8_t *dest_cr     = s->dest[2];

    if (!(IS_FIL(h->mtype)))
        return;

    h261_loop_filter(dest_y,                    linesize);
    h261_loop_filter(dest_y + 8,                linesize);
    h261_loop_filter(dest_y + 8 * linesize,     linesize);
    h261_loop_filter(dest_y + 8 * linesize + 8, linesize);
    h261_loop_filter(dest_cb, uvlinesize);
    h261_loop_filter(dest_cr, uvlinesize);
}