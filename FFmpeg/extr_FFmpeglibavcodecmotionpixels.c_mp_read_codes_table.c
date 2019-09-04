#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int codes_count; int current_codes_count; int /*<<< orphan*/  avctx; TYPE_1__* codes; void* max_codes_bits; } ;
struct TYPE_5__ {void* delta; } ;
typedef  TYPE_2__ MotionPixelsContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int mp_get_code (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mp_read_codes_table(MotionPixelsContext *mp, GetBitContext *gb)
{
    if (mp->codes_count == 1) {
        mp->codes[0].delta = get_bits(gb, 4);
    } else {
        int i;
        int ret;

        mp->max_codes_bits = get_bits(gb, 4);
        for (i = 0; i < mp->codes_count; ++i)
            mp->codes[i].delta = get_bits(gb, 4);
        mp->current_codes_count = 0;
        if ((ret = mp_get_code(mp, gb, 0, 0)) < 0)
            return ret;
        if (mp->current_codes_count < mp->codes_count) {
            av_log(mp->avctx, AV_LOG_ERROR, "too few codes\n");
            return AVERROR_INVALIDDATA;
        }
   }
   return 0;
}