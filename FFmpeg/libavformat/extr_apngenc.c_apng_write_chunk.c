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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVCRC ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CRC_32_IEEE_LE ; 
 int /*<<< orphan*/  AV_WB32 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/  const*) ; 
 size_t av_crc (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * av_crc_get_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void apng_write_chunk(AVIOContext *io_context, uint32_t tag,
                             uint8_t *buf, size_t length)
{
    const AVCRC *crc_table = av_crc_get_table(AV_CRC_32_IEEE_LE);
    uint32_t crc = ~0U;
    uint8_t tagbuf[4];

    av_assert0(crc_table);

    avio_wb32(io_context, length);
    AV_WB32(tagbuf, tag);
    crc = av_crc(crc_table, crc, tagbuf, 4);
    avio_wb32(io_context, tag);
    if (length > 0) {
        crc = av_crc(crc_table, crc, buf, length);
        avio_write(io_context, buf, length);
    }
    avio_wb32(io_context, ~crc);
}