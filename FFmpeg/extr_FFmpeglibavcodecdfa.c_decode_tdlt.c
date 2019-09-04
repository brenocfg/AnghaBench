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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  bytestream2_get_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byteu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_le32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_tdlt(GetByteContext *gb, uint8_t *frame, int width, int height)
{
    const uint8_t *frame_end = frame + width * height;
    uint32_t segments = bytestream2_get_le32(gb);
    int skip, copy;

    while (segments--) {
        if (bytestream2_get_bytes_left(gb) < 2)
            return AVERROR_INVALIDDATA;
        copy = bytestream2_get_byteu(gb) * 2;
        skip = bytestream2_get_byteu(gb) * 2;
        if (frame_end - frame < copy + skip ||
            bytestream2_get_bytes_left(gb) < copy)
            return AVERROR_INVALIDDATA;
        frame += skip;
        bytestream2_get_buffer(gb, frame, copy);
        frame += copy;
    }

    return 0;
}