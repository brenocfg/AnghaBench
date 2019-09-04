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
typedef  int /*<<< orphan*/  RowContext ;
typedef  int /*<<< orphan*/  DNXHDContext ;

/* Variables and functions */
 int dnxhd_decode_dct_block (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dnxhd_decode_dct_block_10_444(const DNXHDContext *ctx,
                                         RowContext *row, int n)
{
    return dnxhd_decode_dct_block(ctx, row, n, 6, 32, 6, 0);
}