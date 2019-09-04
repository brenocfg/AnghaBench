#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {unsigned char** data; int /*<<< orphan*/ * linesize; } ;
struct TYPE_7__ {TYPE_1__* avctx; } ;
struct TYPE_6__ {int height; int width; } ;
typedef  TYPE_2__ CmvContext ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void cmv_decode_intra(CmvContext * s, AVFrame *frame,
                             const uint8_t *buf, const uint8_t *buf_end)
{
    unsigned char *dst = frame->data[0];
    int i;

    for (i=0; i < s->avctx->height && buf_end - buf >= s->avctx->width; i++) {
        memcpy(dst, buf, s->avctx->width);
        dst += frame->linesize[0];
        buf += s->avctx->width;
    }
}