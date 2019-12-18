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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  HEXDUMP_PRINT (char*,...) ; 

__attribute__((used)) static void hex_dump_internal(void *avcl, FILE *f, int level,
                              const uint8_t *buf, int size)
{
    int len, i, j, c;

    for (i = 0; i < size; i += 16) {
        len = size - i;
        if (len > 16)
            len = 16;
        HEXDUMP_PRINT("%08x ", i);
        for (j = 0; j < 16; j++) {
            if (j < len)
                HEXDUMP_PRINT(" %02x", buf[i + j]);
            else
                HEXDUMP_PRINT("   ");
        }
        HEXDUMP_PRINT(" ");
        for (j = 0; j < len; j++) {
            c = buf[i + j];
            if (c < ' ' || c > '~')
                c = '.';
            HEXDUMP_PRINT("%c", c);
        }
        HEXDUMP_PRINT("\n");
    }
}