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
 int /*<<< orphan*/  max_nbits (int*,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void put_swf_line_edge(PutBitContext *pb, int dx, int dy)
{
    int nbits, mask;

    put_bits(pb, 1, 1); /* edge */
    put_bits(pb, 1, 1); /* line select */
    nbits = 2;
    max_nbits(&nbits, dx);
    max_nbits(&nbits, dy);

    mask = (1 << nbits) - 1;
    put_bits(pb, 4, nbits - 2); /* 16 bits precision */
    if (dx == 0) {
        put_bits(pb, 1, 0);
        put_bits(pb, 1, 1);
        put_bits(pb, nbits, dy & mask);
    } else if (dy == 0) {
        put_bits(pb, 1, 0);
        put_bits(pb, 1, 0);
        put_bits(pb, nbits, dx & mask);
    } else {
        put_bits(pb, 1, 1);
        put_bits(pb, nbits, dx & mask);
        put_bits(pb, nbits, dy & mask);
    }
}