#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__* shift_lsbs; } ;
struct TYPE_10__ {int /*<<< orphan*/  mc_coding; } ;
struct TYPE_11__ {scalar_t__ js_switch; TYPE_1__ sconf; int /*<<< orphan*/  gb; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ ALSSpecificConfig ;
typedef  TYPE_2__ ALSDecContext ;
typedef  TYPE_3__ ALSBlockData ;

/* Variables and functions */
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int read_const_block_data (TYPE_2__*,TYPE_3__*) ; 
 int read_var_block_data (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static int read_block(ALSDecContext *ctx, ALSBlockData *bd)
{
    int ret;
    GetBitContext *gb        = &ctx->gb;
    ALSSpecificConfig *sconf = &ctx->sconf;

    *bd->shift_lsbs = 0;
    // read block type flag and read the samples accordingly
    if (get_bits1(gb)) {
        ret = read_var_block_data(ctx, bd);
    } else {
        ret = read_const_block_data(ctx, bd);
    }

    if (!sconf->mc_coding || ctx->js_switch)
        align_get_bits(gb);

    return ret;
}