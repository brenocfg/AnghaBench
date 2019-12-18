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
struct TYPE_6__ {TYPE_1__ pc; int /*<<< orphan*/  sei; int /*<<< orphan*/  pkt; int /*<<< orphan*/  ps; } ;
typedef  TYPE_2__ HEVCParserContext ;
typedef  TYPE_3__ AVCodecParserContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_h2645_packet_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_hevc_ps_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_hevc_reset_sei (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hevc_parser_close(AVCodecParserContext *s)
{
    HEVCParserContext *ctx = s->priv_data;

    ff_hevc_ps_uninit(&ctx->ps);
    ff_h2645_packet_uninit(&ctx->pkt);
    ff_hevc_reset_sei(&ctx->sei);

    av_freep(&ctx->pc.buffer);
}