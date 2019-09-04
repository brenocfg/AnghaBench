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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  av_mod_uintp2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void put_sbits(PutBitContext *pb, int n, int32_t value)
{
    av_assert2(n >= 0 && n <= 31);

    put_bits(pb, n, av_mod_uintp2(value, n));
}