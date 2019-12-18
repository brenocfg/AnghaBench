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
typedef  enum HapSectionType { ____Placeholder_HapSectionType } HapSectionType ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le24 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 

int ff_hap_parse_section_header(GetByteContext *gbc, int *section_size,
                                enum HapSectionType *section_type)
{
    if (bytestream2_get_bytes_left(gbc) < 4)
        return AVERROR_INVALIDDATA;

    *section_size = bytestream2_get_le24(gbc);
    *section_type = bytestream2_get_byte(gbc);

    if (*section_size == 0) {
        if (bytestream2_get_bytes_left(gbc) < 4)
            return AVERROR_INVALIDDATA;

        *section_size = bytestream2_get_le32(gbc);
    }

    if (*section_size > bytestream2_get_bytes_left(gbc) || *section_size < 0)
        return AVERROR_INVALIDDATA;
    else
        return 0;
}