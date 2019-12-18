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
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  pixel4 ;
typedef  int /*<<< orphan*/  pixel ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RN4PA (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_WN4PA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vert_8x8_c(uint8_t *_dst, ptrdiff_t stride,
                       const uint8_t *left, const uint8_t *_top)
{
    pixel *dst = (pixel *) _dst;
    const pixel *top = (const pixel *) _top;
    pixel4 p4a = AV_RN4PA(top + 0);
    pixel4 p4b = AV_RN4PA(top + 4);
    int y;

    stride /= sizeof(pixel);
    for (y = 0; y < 8; y++) {
        AV_WN4PA(dst + 0, p4a);
        AV_WN4PA(dst + 4, p4b);
        dst += stride;
    }
}