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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int getbit(GetByteContext *gb, uint32_t *bitbuf, int *bits)
{
    int ret;

    if (!*bits) {
        *bitbuf = bytestream2_get_le32(gb);
        *bits = 32;
    }

    ret = *bitbuf >> 31;
    *bitbuf <<= 1;
    (*bits)--;

    return ret;
}