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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 size_t* ff_zigzag_direct ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

void ff_write_quant_matrix(PutBitContext *pb, uint16_t *matrix)
{
    int i;

    if (matrix) {
        put_bits(pb, 1, 1);
        for (i = 0; i < 64; i++) {
            put_bits(pb, 8, matrix[ff_zigzag_direct[i]]);
        }
    } else
        put_bits(pb, 1, 0);
}