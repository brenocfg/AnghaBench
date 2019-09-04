#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int GSM_FRAME_SIZE ; 
 int GSM_MS_BLOCK_SIZE ; 
 int gsm_decode_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int ff_msgsm_decode_block(AVCodecContext *avctx, int16_t *samples,
                          const uint8_t *buf, int mode)
{
    int res;
    GetBitContext gb;
    init_get_bits(&gb, buf, GSM_MS_BLOCK_SIZE * 8);
    res = gsm_decode_block(avctx, samples, &gb, mode);
    if (res < 0)
        return res;
    return gsm_decode_block(avctx, samples + GSM_FRAME_SIZE, &gb, mode);
}