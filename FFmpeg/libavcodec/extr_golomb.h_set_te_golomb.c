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
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  set_ue_golomb (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void set_te_golomb(PutBitContext *pb, int i, int range)
{
    av_assert2(range >= 1);
    av_assert2(i <= range);

    if (range == 2)
        put_bits(pb, 1, i ^ 1);
    else
        set_ue_golomb(pb, i);
}