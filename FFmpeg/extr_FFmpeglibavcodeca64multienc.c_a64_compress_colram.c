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

/* Variables and functions */

__attribute__((used)) static void a64_compress_colram(unsigned char *buf, int *charmap, uint8_t *colram)
{
    int a;
    uint8_t temp;
    /* only needs to be done in 5col mode */
    /* XXX could be squeezed to 0x80 bytes */
    for (a = 0; a < 256; a++) {
        temp  = colram[charmap[a + 0x000]] << 0;
        temp |= colram[charmap[a + 0x100]] << 1;
        temp |= colram[charmap[a + 0x200]] << 2;
        if (a < 0xe8) temp |= colram[charmap[a + 0x300]] << 3;
        buf[a] = temp << 2;
    }
}