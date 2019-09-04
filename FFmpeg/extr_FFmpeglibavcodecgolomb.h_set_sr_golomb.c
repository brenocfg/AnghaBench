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
 int /*<<< orphan*/  set_ur_golomb (int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static inline void set_sr_golomb(PutBitContext *pb, int i, int k, int limit,
                                 int esc_len)
{
    int v;

    v  = -2 * i - 1;
    v ^= (v >> 31);

    set_ur_golomb(pb, v, k, limit, esc_len);
}