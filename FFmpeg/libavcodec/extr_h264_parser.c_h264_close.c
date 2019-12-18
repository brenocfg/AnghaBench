#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_6__ {int /*<<< orphan*/  ps; int /*<<< orphan*/  sei; TYPE_1__ pc; } ;
typedef  TYPE_1__ ParseContext ;
typedef  TYPE_2__ H264ParseContext ;
typedef  TYPE_3__ AVCodecParserContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_h264_ps_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_h264_sei_uninit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void h264_close(AVCodecParserContext *s)
{
    H264ParseContext *p = s->priv_data;
    ParseContext *pc = &p->pc;

    av_freep(&pc->buffer);

    ff_h264_sei_uninit(&p->sei);
    ff_h264_ps_uninit(&p->ps);
}