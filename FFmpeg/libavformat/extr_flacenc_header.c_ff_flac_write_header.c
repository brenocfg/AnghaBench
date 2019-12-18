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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int FLAC_STREAMINFO_SIZE ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int*,int) ; 

int ff_flac_write_header(AVIOContext *pb, uint8_t *extradata,
                         int extradata_size, int last_block)
{
    uint8_t header[8] = {
        0x66, 0x4C, 0x61, 0x43, 0x00, 0x00, 0x00, 0x22
    };

    header[4] = last_block ? 0x80 : 0x00;

    if (extradata_size < FLAC_STREAMINFO_SIZE)
        return AVERROR_INVALIDDATA;

    /* write "fLaC" stream marker and first metadata block header */
    avio_write(pb, header, 8);

    /* write STREAMINFO */
    avio_write(pb, extradata, FLAC_STREAMINFO_SIZE);

    return 0;
}