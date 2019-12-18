#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* shift_lsbs; unsigned int block_length; unsigned int* raw_samples; scalar_t__* const_block; } ;
typedef  int /*<<< orphan*/  ALSDecContext ;
typedef  TYPE_1__ ALSBlockData ;

/* Variables and functions */
 int /*<<< orphan*/  decode_const_block_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int decode_var_block_data (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int decode_block(ALSDecContext *ctx, ALSBlockData *bd)
{
    unsigned int smp;
    int ret = 0;

    // read block type flag and read the samples accordingly
    if (*bd->const_block)
        decode_const_block_data(ctx, bd);
    else
        ret = decode_var_block_data(ctx, bd); // always return 0

    if (ret < 0)
        return ret;

    // TODO: read RLSLMS extension data

    if (*bd->shift_lsbs)
        for (smp = 0; smp < bd->block_length; smp++)
            bd->raw_samples[smp] = (unsigned)bd->raw_samples[smp] << *bd->shift_lsbs;

    return 0;
}