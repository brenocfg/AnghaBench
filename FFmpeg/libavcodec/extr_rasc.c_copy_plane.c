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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int height; TYPE_1__* priv_data; } ;
struct TYPE_8__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_7__ {int /*<<< orphan*/  stride; } ;
typedef  TYPE_1__ RASCContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_plane(AVCodecContext *avctx, AVFrame *src, AVFrame *dst)
{
    RASCContext *s = avctx->priv_data;
    uint8_t *srcp = src->data[0];
    uint8_t *dstp = dst->data[0];

    for (int y = 0; y < avctx->height; y++) {
        memcpy(dstp, srcp, s->stride);
        srcp += src->linesize[0];
        dstp += dst->linesize[0];
    }
}