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
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int GIF_EXTENSION_INTRODUCER ; 
 int GIF_GCE_EXT_LABEL ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gif_parse_packet(AVFormatContext *s, uint8_t *data, int size)
{
    GetByteContext gb;
    int x;

    bytestream2_init(&gb, data, size);

    while (bytestream2_get_bytes_left(&gb) > 0) {
        x = bytestream2_get_byte(&gb);
        if (x != GIF_EXTENSION_INTRODUCER)
            return 0;

        x = bytestream2_get_byte(&gb);
        while (x != GIF_GCE_EXT_LABEL && bytestream2_get_bytes_left(&gb) > 0) {
            int block_size = bytestream2_get_byte(&gb);
            if (!block_size)
                break;
            bytestream2_skip(&gb, block_size);
        }

        if (x == GIF_GCE_EXT_LABEL)
            return bytestream2_tell(&gb) + 2;
    }

    return 0;
}