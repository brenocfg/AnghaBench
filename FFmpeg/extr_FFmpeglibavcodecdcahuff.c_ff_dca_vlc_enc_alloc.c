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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 int /*<<< orphan*/ ** bitalloc_12_bits ; 
 int /*<<< orphan*/ ** bitalloc_12_codes ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ff_dca_vlc_enc_alloc(PutBitContext *pb, int *values, uint8_t n, uint8_t sel)
{
    uint8_t i, id;
    for (i = 0; i < n; i++) {
        id = values[i] - 1;
        put_bits(pb, bitalloc_12_bits[sel][id], bitalloc_12_codes[sel][id]);
    }
}