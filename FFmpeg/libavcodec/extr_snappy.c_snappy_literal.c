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
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  bytestream2_get_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 unsigned int bytestream2_get_le16 (int /*<<< orphan*/ *) ; 
 unsigned int bytestream2_get_le24 (int /*<<< orphan*/ *) ; 
 unsigned int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snappy_literal(GetByteContext *gb, uint8_t *p, int size, int val)
{
    unsigned int len = 1;

    switch (val) {
    case 63:
        len += bytestream2_get_le32(gb);
        break;
    case 62:
        len += bytestream2_get_le24(gb);
        break;
    case 61:
        len += bytestream2_get_le16(gb);
        break;
    case 60:
        len += bytestream2_get_byte(gb);
        break;
    default: // val < 60
        len += val;
    }

    if (size < len)
        return AVERROR_INVALIDDATA;

    bytestream2_get_buffer(gb, p, len);

    return len;
}