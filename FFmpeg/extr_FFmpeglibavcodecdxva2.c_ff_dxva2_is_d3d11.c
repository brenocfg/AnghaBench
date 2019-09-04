#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pix_fmt; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_D3D11 ; 
 scalar_t__ AV_PIX_FMT_D3D11VA_VLD ; 
 scalar_t__ CONFIG_D3D11VA ; 

int ff_dxva2_is_d3d11(const AVCodecContext *avctx)
{
    if (CONFIG_D3D11VA)
        return avctx->pix_fmt == AV_PIX_FMT_D3D11VA_VLD ||
               avctx->pix_fmt == AV_PIX_FMT_D3D11;
    else
        return 0;
}