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
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  mss2_blit_wmv9_template (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void mss2_blit_wmv9_masked_c(uint8_t *dst, ptrdiff_t dst_stride,
                                    int maskcolor, const uint8_t *mask,
                                    ptrdiff_t mask_stride,
                                    const uint8_t *srcy, ptrdiff_t srcy_stride,
                                    const uint8_t *srcu, const uint8_t *srcv,
                                    ptrdiff_t srcuv_stride, int w, int h)
{
    mss2_blit_wmv9_template(dst, dst_stride, 0, 1,
                            maskcolor, mask, mask_stride,
                            srcy, srcy_stride,
                            srcu, srcv, srcuv_stride,
                            w, h);
}