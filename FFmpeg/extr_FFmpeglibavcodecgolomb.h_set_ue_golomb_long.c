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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 int UINT32_MAX ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int av_log2 (int) ; 
 int /*<<< orphan*/ * ff_ue_golomb_len ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_bits64 (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void set_ue_golomb_long(PutBitContext *pb, uint32_t i)
{
    av_assert2(i <= (UINT32_MAX - 1));

    if (i < 256)
        put_bits(pb, ff_ue_golomb_len[i], i + 1);
    else {
        int e = av_log2(i + 1);
        put_bits64(pb, 2 * e + 1, i + 1);
    }
}