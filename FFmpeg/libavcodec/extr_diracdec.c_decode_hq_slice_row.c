#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int num_x; int thread_buf_size; int /*<<< orphan*/ * thread_buf; } ;
typedef  int /*<<< orphan*/  DiracSlice ;
typedef  TYPE_1__ DiracContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  decode_hq_slice (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_hq_slice_row(AVCodecContext *avctx, void *arg, int jobnr, int threadnr)
{
    int i;
    DiracContext *s = avctx->priv_data;
    DiracSlice *slices = ((DiracSlice *)arg) + s->num_x*jobnr;
    uint8_t *thread_buf = &s->thread_buf[s->thread_buf_size*threadnr];
    for (i = 0; i < s->num_x; i++)
        decode_hq_slice(s, &slices[i], thread_buf);
    return 0;
}