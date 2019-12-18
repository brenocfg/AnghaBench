#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ BSFCompatContext ;
typedef  TYPE_2__ AVBitStreamFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_bsf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (TYPE_2__*) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 

void av_bitstream_filter_close(AVBitStreamFilterContext *bsfc)
{
    BSFCompatContext *priv;

    if (!bsfc)
        return;

    priv = bsfc->priv_data;

    av_bsf_free(&priv->ctx);
    av_freep(&bsfc->priv_data);
    av_free(bsfc);
}