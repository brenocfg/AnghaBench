#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* priv_data; } ;
struct TYPE_7__ {int** offset; int /*<<< orphan*/  V; } ;
struct TYPE_6__ {int /*<<< orphan*/  crc_ctx; } ;
struct TYPE_8__ {TYPE_2__ dsp; TYPE_1__ frame; } ;
typedef  TYPE_3__ SBCDecContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CRC_8_EBU ; 
 int FF_ARRAY_ELEMS (int*) ; 
 int /*<<< orphan*/  av_crc_get_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sbc_decode_init(AVCodecContext *avctx)
{
    SBCDecContext *sbc = avctx->priv_data;
    int i, ch;

    sbc->frame.crc_ctx = av_crc_get_table(AV_CRC_8_EBU);

    memset(sbc->dsp.V, 0, sizeof(sbc->dsp.V));
    for (ch = 0; ch < 2; ch++)
        for (i = 0; i < FF_ARRAY_ELEMS(sbc->dsp.offset[0]); i++)
            sbc->dsp.offset[ch][i] = (10 * i + 10);
    return 0;
}