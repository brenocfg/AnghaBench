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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  decompress_indices (int*,int const*) ; 
 int extract_component (int,int,int) ; 

__attribute__((used)) static void yao_subblock(uint8_t *dst, uint8_t *yo_indices,
                        ptrdiff_t stride, const uint8_t *block)
{
    uint8_t yo0 = *(block);
    uint8_t yo1 = *(block + 1);
    int x, y;

    decompress_indices(yo_indices, block + 2);

    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            int yo_code = yo_indices[x + y * 4];

            dst[x] = extract_component(yo0, yo1, yo_code);
        }
        dst += stride;
    }
}