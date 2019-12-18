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

/* Variables and functions */
 int /*<<< orphan*/  compress_alpha (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compress_color (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rgba2ycocg (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int dxt5ys_block(uint8_t *dst, ptrdiff_t stride, const uint8_t *block)
{
    int x, y;
    uint8_t reorder[64];

    /* Reorder the components and then run a normal DXT5 compression. */
    for (y = 0; y < 4; y++)
        for (x = 0; x < 4; x++)
            rgba2ycocg(reorder + x * 4 + y * 16, block + x * 4 + y * stride);

    compress_alpha(dst + 0, 16, reorder);
    compress_color(dst + 8, 16, reorder);

    return 16;
}