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
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_RB16 (char*) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le16u (int /*<<< orphan*/ *) ; 
 int ff_tget_long (int /*<<< orphan*/ *,int) ; 
 int ff_tget_short (int /*<<< orphan*/ *,int) ; 

int ff_tdecode_header(GetByteContext *gb, int *le, int *ifd_offset)
{
    if (bytestream2_get_bytes_left(gb) < 8) {
        return AVERROR_INVALIDDATA;
    }

    *le = bytestream2_get_le16u(gb);
    if (*le == AV_RB16("II")) {
        *le = 1;
    } else if (*le == AV_RB16("MM")) {
        *le = 0;
    } else {
        return AVERROR_INVALIDDATA;
    }

    if (ff_tget_short(gb, *le) != 42) {
        return AVERROR_INVALIDDATA;
    }

    *ifd_offset = ff_tget_long(gb, *le);

    return 0;
}