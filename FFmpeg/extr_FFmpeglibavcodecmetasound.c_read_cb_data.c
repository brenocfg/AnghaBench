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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum TwinVQFrameType { ____Placeholder_TwinVQFrameType } TwinVQFrameType ;
struct TYPE_3__ {int* n_div; int* bits_main_spec_change; int /*<<< orphan*/ *** bits_main_spec; } ;
typedef  TYPE_1__ TwinVQContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 void* get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_cb_data(TwinVQContext *tctx, GetBitContext *gb,
                         uint8_t *dst, enum TwinVQFrameType ftype)
{
    int i;

    for (i = 0; i < tctx->n_div[ftype]; i++) {
        int bs_second_part = (i >= tctx->bits_main_spec_change[ftype]);

        *dst++ = get_bits(gb, tctx->bits_main_spec[0][ftype][bs_second_part]);
        *dst++ = get_bits(gb, tctx->bits_main_spec[1][ftype][bs_second_part]);
    }
}