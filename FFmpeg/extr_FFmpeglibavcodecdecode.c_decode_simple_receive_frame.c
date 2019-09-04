#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVFrame ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int decode_simple_internal (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int decode_simple_receive_frame(AVCodecContext *avctx, AVFrame *frame)
{
    int ret;

    while (!frame->buf[0]) {
        ret = decode_simple_internal(avctx, frame);
        if (ret < 0)
            return ret;
    }

    return 0;
}