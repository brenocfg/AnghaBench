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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  LD4 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void ff_put_h264_qpel8_mc00_msa(uint8_t *dst, const uint8_t *src,
                                ptrdiff_t stride)
{
    uint64_t src0, src1, src2, src3, src4, src5, src6, src7;

    LD4(src, stride, src0, src1, src2, src3);
    src += 4 * stride;
    LD4(src, stride, src4, src5, src6, src7);
    SD4(src0, src1, src2, src3, dst, stride);
    dst += 4 * stride;
    SD4(src4, src5, src6, src7, dst, stride);
}