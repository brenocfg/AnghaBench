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
typedef  enum HapHeaderLength { ____Placeholder_HapHeaderLength } HapHeaderLength ;
typedef  int /*<<< orphan*/  PutByteContext ;

/* Variables and functions */
 int HAP_HDR_LONG ; 
 int /*<<< orphan*/  bytestream2_put_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream2_put_le24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream2_put_le32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hap_write_section_header(PutByteContext *pbc,
                                     enum HapHeaderLength header_length,
                                     int section_length,
                                     enum HapSectionType section_type)
{
    /* The first three bytes are the length of the section (not including the
     * header) or zero if using an eight-byte header.
     * For an eight-byte header, the length is in the last four bytes.
     * The fourth byte stores the section type. */
    bytestream2_put_le24(pbc, header_length == HAP_HDR_LONG ? 0 : section_length);
    bytestream2_put_byte(pbc, section_type);

    if (header_length == HAP_HDR_LONG) {
        bytestream2_put_le32(pbc, section_length);
    }
}