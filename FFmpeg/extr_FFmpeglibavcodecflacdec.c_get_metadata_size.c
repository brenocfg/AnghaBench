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

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  flac_parse_block_header (int /*<<< orphan*/  const*,int*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int get_metadata_size(const uint8_t *buf, int buf_size)
{
    int metadata_last, metadata_size;
    const uint8_t *buf_end = buf + buf_size;

    buf += 4;
    do {
        if (buf_end - buf < 4)
            return AVERROR_INVALIDDATA;
        flac_parse_block_header(buf, &metadata_last, NULL, &metadata_size);
        buf += 4;
        if (buf_end - buf < metadata_size) {
            /* need more data in order to read the complete header */
            return AVERROR_INVALIDDATA;
        }
        buf += metadata_size;
    } while (!metadata_last);

    return buf_size - (buf_end - buf);
}