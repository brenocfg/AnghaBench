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
typedef  int int8_t ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int bytestream2_get_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byteu (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le16 (int /*<<< orphan*/ *) ; 
 int bytestream2_peek_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int decode_bdlt(GetByteContext *gb, uint8_t *frame, int width, int height)
{
    uint8_t *line_ptr;
    int count, lines, segments;

    count = bytestream2_get_le16(gb);
    if (count >= height)
        return AVERROR_INVALIDDATA;
    frame += width * count;
    lines = bytestream2_get_le16(gb);
    if (count + lines > height)
        return AVERROR_INVALIDDATA;

    while (lines--) {
        if (bytestream2_get_bytes_left(gb) < 1)
            return AVERROR_INVALIDDATA;
        line_ptr = frame;
        frame += width;
        segments = bytestream2_get_byteu(gb);
        while (segments--) {
            if (frame - line_ptr <= bytestream2_peek_byte(gb))
                return AVERROR_INVALIDDATA;
            line_ptr += bytestream2_get_byte(gb);
            count = (int8_t)bytestream2_get_byte(gb);
            if (count >= 0) {
                if (frame - line_ptr < count)
                    return AVERROR_INVALIDDATA;
                if (bytestream2_get_buffer(gb, line_ptr, count) != count)
                    return AVERROR_INVALIDDATA;
            } else {
                count = -count;
                if (frame - line_ptr < count)
                    return AVERROR_INVALIDDATA;
                memset(line_ptr, bytestream2_get_byte(gb), count);
            }
            line_ptr += count;
        }
    }

    return 0;
}