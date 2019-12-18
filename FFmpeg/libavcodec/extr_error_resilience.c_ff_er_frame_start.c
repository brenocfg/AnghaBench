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
struct TYPE_5__ {int /*<<< orphan*/  error_concealment; } ;
struct TYPE_4__ {int mecc_inited; int mb_stride; int mb_height; int mb_num; scalar_t__ error_occurred; int /*<<< orphan*/  error_count; int /*<<< orphan*/  error_status_table; TYPE_2__* avctx; int /*<<< orphan*/  mecc; } ;
typedef  TYPE_1__ ERContext ;

/* Variables and functions */
 int ER_MB_END ; 
 int ER_MB_ERROR ; 
 int VP_START ; 
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_me_cmp_init (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

void ff_er_frame_start(ERContext *s)
{
    if (!s->avctx->error_concealment)
        return;

    if (!s->mecc_inited) {
        ff_me_cmp_init(&s->mecc, s->avctx);
        s->mecc_inited = 1;
    }

    memset(s->error_status_table, ER_MB_ERROR | VP_START | ER_MB_END,
           s->mb_stride * s->mb_height * sizeof(uint8_t));
    atomic_init(&s->error_count, 3 * s->mb_num);
    s->error_occurred = 0;
}