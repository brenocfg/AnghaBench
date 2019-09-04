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
 int /*<<< orphan*/  yao_subblock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int yo_block(uint8_t *dst, ptrdiff_t stride,
                    uint8_t *unused0, ptrdiff_t unused1,
                    const uint8_t *block)
{
    uint8_t yo_indices[16];

    yao_subblock(dst,      yo_indices, stride, block);
    yao_subblock(dst + 4,  yo_indices, stride, block + 8);
    yao_subblock(dst + 8,  yo_indices, stride, block + 16);
    yao_subblock(dst + 12, yo_indices, stride, block + 24);

    return 32;
}