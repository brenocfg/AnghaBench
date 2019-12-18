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
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR_BUFFER_TOO_SMALL ; 
#define  SNAPPY_COPY_1 131 
#define  SNAPPY_COPY_2 130 
#define  SNAPPY_COPY_4 129 
#define  SNAPPY_LITERAL 128 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 scalar_t__ decode_len (int /*<<< orphan*/ *) ; 
 int snappy_copy1 (int /*<<< orphan*/ *,int*,int*,scalar_t__,int) ; 
 int snappy_copy2 (int /*<<< orphan*/ *,int*,int*,scalar_t__,int) ; 
 int snappy_copy4 (int /*<<< orphan*/ *,int*,int*,scalar_t__,int) ; 
 int snappy_literal (int /*<<< orphan*/ *,int*,scalar_t__,int) ; 

int ff_snappy_uncompress(GetByteContext *gb, uint8_t *buf, int64_t *size)
{
    int64_t len = decode_len(gb);
    int ret     = 0;
    uint8_t *p;

    if (len < 0)
        return len;

    if (len > *size)
        return AVERROR_BUFFER_TOO_SMALL;

    *size = len;
    p     = buf;

    while (bytestream2_get_bytes_left(gb) > 0) {
        uint8_t s = bytestream2_get_byte(gb);
        int val   = s >> 2;

        switch (s & 0x03) {
        case SNAPPY_LITERAL:
            ret = snappy_literal(gb, p, len, val);
            break;
        case SNAPPY_COPY_1:
            ret = snappy_copy1(gb, buf, p, len, val);
            break;
        case SNAPPY_COPY_2:
            ret = snappy_copy2(gb, buf, p, len, val);
            break;
        case SNAPPY_COPY_4:
            ret = snappy_copy4(gb, buf, p, len, val);
            break;
        }

        if (ret < 0)
            return ret;

        p   += ret;
        len -= ret;
    }

    return 0;
}