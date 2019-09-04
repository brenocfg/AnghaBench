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
struct TYPE_5__ {scalar_t__ has_status; } ;
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ AVCodecContext ;
typedef  TYPE_2__ ADPCMDecodeContext ;

/* Variables and functions */

__attribute__((used)) static void adpcm_flush(AVCodecContext *avctx)
{
    ADPCMDecodeContext *c = avctx->priv_data;
    c->has_status = 0;
}