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
struct TYPE_4__ {int num_streams; scalar_t__ current_stream; int /*<<< orphan*/  offset; int /*<<< orphan*/ * xma; } ;
typedef  TYPE_1__ XMADecodeCtx ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xma_flush(AVCodecContext *avctx)
{
    XMADecodeCtx *s = avctx->priv_data;
    int i;

    for (i = 0; i < s->num_streams; i++)
        flush(&s->xma[i]);

    memset(s->offset, 0, sizeof(s->offset));
    s->current_stream = 0;
}