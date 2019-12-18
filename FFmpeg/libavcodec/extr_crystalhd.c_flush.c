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
struct TYPE_4__ {int /*<<< orphan*/  dev; scalar_t__ draining; scalar_t__ need_second_field; } ;
typedef  TYPE_1__ CHDContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  DtsFlushInput (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void flush(AVCodecContext *avctx)
{
    CHDContext *priv = avctx->priv_data;

    priv->need_second_field = 0;
    priv->draining          = 0;

    /* Flush mode 4 flushes all software and hardware buffers. */
    DtsFlushInput(priv->dev, 4);
}