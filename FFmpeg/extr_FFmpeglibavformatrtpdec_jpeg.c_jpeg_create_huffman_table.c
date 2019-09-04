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
typedef  int /*<<< orphan*/  PutByteContext ;

/* Variables and functions */
 int /*<<< orphan*/  bytestream2_put_byte (int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static int jpeg_create_huffman_table(PutByteContext *p, int table_class,
                                     int table_id, const uint8_t *bits_table,
                                     const uint8_t *value_table)
{
    int i, n = 0;

    bytestream2_put_byte(p, table_class << 4 | table_id);

    for (i = 1; i <= 16; i++) {
        n += bits_table[i];
        bytestream2_put_byte(p, bits_table[i]);
    }

    for (i = 0; i < n; i++) {
        bytestream2_put_byte(p, value_table[i]);
    }
    return n + 17;
}