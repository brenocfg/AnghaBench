#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_3__ {int /*<<< orphan*/  fill_val; int /*<<< orphan*/  coef_model; } ;
typedef  int /*<<< orphan*/  RangeCoder ;
typedef  TYPE_1__ FillBlockCoder ;

/* Variables and functions */
 scalar_t__ decode_coeff (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void decode_fill_block(RangeCoder *c, FillBlockCoder *fc,
                              uint8_t *dst, ptrdiff_t stride, int block_size)
{
    int i;

    fc->fill_val += decode_coeff(c, &fc->coef_model);

    for (i = 0; i < block_size; i++, dst += stride)
        memset(dst, fc->fill_val, block_size);
}