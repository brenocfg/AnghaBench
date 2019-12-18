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
 int /*<<< orphan*/  dxt5_block_internal (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ycocg2rgba (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dxt5y_block(uint8_t *dst, ptrdiff_t stride, const uint8_t *block)
{
    int x, y;

    /* This format is basically DXT5, with luma stored in alpha.
     * Run a normal decompress and then reorder the components. */
    dxt5_block_internal(dst, stride, block);

    for (y = 0; y < 4; y++)
        for (x = 0; x < 4; x++)
            ycocg2rgba(dst + x * 4 + y * stride, 0);

    return 16;
}