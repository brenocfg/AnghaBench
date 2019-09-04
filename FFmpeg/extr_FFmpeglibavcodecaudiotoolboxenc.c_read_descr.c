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
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_descr(GetByteContext *gb, int *tag)
{
    int len = 0;
    int count = 4;
    *tag = bytestream2_get_byte(gb);
    while (count--) {
        int c = bytestream2_get_byte(gb);
        len = (len << 7) | (c & 0x7f);
        if (!(c & 0x80))
            break;
    }
    return len;
}