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
struct TYPE_5__ {int /*<<< orphan*/  write_buffer; int /*<<< orphan*/  frame_header_ref; int /*<<< orphan*/  sequence_header_ref; } ;
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ CodedBitstreamContext ;
typedef  TYPE_2__ CodedBitstreamAV1Context ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cbs_av1_close(CodedBitstreamContext *ctx)
{
    CodedBitstreamAV1Context *priv = ctx->priv_data;

    av_buffer_unref(&priv->sequence_header_ref);
    av_buffer_unref(&priv->frame_header_ref);

    av_freep(&priv->write_buffer);
}