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
 scalar_t__ FF_ARRAY_ELEMS (int*) ; 
 int av_clip (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ decode_rice (int /*<<< orphan*/ *,int) ; 
 int* mcc_weightings ; 

__attribute__((used)) static inline int als_weighting(GetBitContext *gb, int k, int off)
{
    int idx = av_clip(decode_rice(gb, k) + off,
                      0, FF_ARRAY_ELEMS(mcc_weightings) - 1);
    return mcc_weightings[idx];
}