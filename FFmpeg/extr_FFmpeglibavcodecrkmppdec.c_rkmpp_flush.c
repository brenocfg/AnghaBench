#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* priv_data; } ;
struct TYPE_11__ {TYPE_1__* decoder_ref; } ;
struct TYPE_10__ {int first_packet; int /*<<< orphan*/  ctx; TYPE_2__* mpi; } ;
struct TYPE_9__ {int (* reset ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {scalar_t__ data; } ;
typedef  TYPE_3__ RKMPPDecoder ;
typedef  TYPE_4__ RKMPPDecodeContext ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int MPP_NOK ; 
 int MPP_OK ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rkmpp_flush(AVCodecContext *avctx)
{
    RKMPPDecodeContext *rk_context = avctx->priv_data;
    RKMPPDecoder *decoder = (RKMPPDecoder *)rk_context->decoder_ref->data;
    int ret = MPP_NOK;

    av_log(avctx, AV_LOG_DEBUG, "Flush.\n");

    ret = decoder->mpi->reset(decoder->ctx);
    if (ret == MPP_OK) {
        decoder->first_packet = 1;
    } else
        av_log(avctx, AV_LOG_ERROR, "Failed to reset MPI (code = %d)\n", ret);
}