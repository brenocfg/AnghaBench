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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 unsigned int get_ue_golomb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int get_ue_code(GetBitContext *gb, int order)
{
    unsigned ret = get_ue_golomb(gb);
    if (ret >= ((1U<<31)>>order)) {
        av_log(NULL, AV_LOG_ERROR, "get_ue_code: value too larger\n");
        return AVERROR_INVALIDDATA;
    }
    if (order) {
        return (ret<<order) + get_bits(gb, order);
    }
    return ret;
}