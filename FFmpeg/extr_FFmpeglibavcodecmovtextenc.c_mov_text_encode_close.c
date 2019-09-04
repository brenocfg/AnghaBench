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
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  ass_ctx; } ;
typedef  TYPE_1__ MovTextContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprint_finalize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_ass_split_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_text_encode_close(AVCodecContext *avctx)
{
    MovTextContext *s = avctx->priv_data;
    ff_ass_split_free(s->ass_ctx);
    av_bprint_finalize(&s->buffer, NULL);
    return 0;
}