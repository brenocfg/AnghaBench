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
struct TYPE_3__ {int /*<<< orphan*/ * priv_data; } ;
typedef  int /*<<< orphan*/  SubBand ;
typedef  int /*<<< orphan*/  DiracContext ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int decode_subband_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_subband_golomb(AVCodecContext *avctx, void *arg)
{
    DiracContext *s = avctx->priv_data;
    SubBand **b     = arg;
    return decode_subband_internal(s, *b, 0);
}