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
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_sbits (int /*<<< orphan*/ *,int,int) ; 

void ff_flv2_encode_ac_esc(PutBitContext *pb, int slevel, int level,
                           int run, int last)
{
    if (level < 64) { // 7-bit level
        put_bits(pb, 1, 0);
        put_bits(pb, 1, last);
        put_bits(pb, 6, run);

        put_sbits(pb, 7, slevel);
    } else {
        /* 11-bit level */
        put_bits(pb, 1, 1);
        put_bits(pb, 1, last);
        put_bits(pb, 6, run);

        put_sbits(pb, 11, slevel);
    }
}