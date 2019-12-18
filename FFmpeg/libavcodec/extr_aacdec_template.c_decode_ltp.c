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
struct TYPE_3__ {size_t lag; int /*<<< orphan*/ * used; int /*<<< orphan*/  coef; } ;
typedef  TYPE_1__ LongTermPrediction ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_LTP_LONG_SFB ; 
 size_t get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ltp_coef ; 

__attribute__((used)) static void decode_ltp(LongTermPrediction *ltp,
                       GetBitContext *gb, uint8_t max_sfb)
{
    int sfb;

    ltp->lag  = get_bits(gb, 11);
    ltp->coef = ltp_coef[get_bits(gb, 3)];
    for (sfb = 0; sfb < FFMIN(max_sfb, MAX_LTP_LONG_SFB); sfb++)
        ltp->used[sfb] = get_bits1(gb);
}