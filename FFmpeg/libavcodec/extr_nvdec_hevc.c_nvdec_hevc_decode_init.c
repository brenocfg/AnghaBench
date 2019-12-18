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
struct TYPE_8__ {TYPE_1__* internal; } ;
struct TYPE_7__ {int supports_444; } ;
struct TYPE_6__ {TYPE_2__* hwaccel_priv_data; } ;
typedef  TYPE_2__ NVDECContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int ff_nvdec_decode_init (TYPE_3__*) ; 

__attribute__((used)) static int nvdec_hevc_decode_init(AVCodecContext *avctx) {
    NVDECContext *ctx = avctx->internal->hwaccel_priv_data;
    ctx->supports_444 = 1;
    return ff_nvdec_decode_init(avctx);
}