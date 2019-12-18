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
typedef  size_t u16 ;
struct orinoco_fw_header {int /*<<< orphan*/  compat_offset; int /*<<< orphan*/  pri_offset; int /*<<< orphan*/  pdr_offset; int /*<<< orphan*/  block_offset; int /*<<< orphan*/  headersize; int /*<<< orphan*/  hdr_vers; } ;

/* Variables and functions */
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static const char *validate_fw(const struct orinoco_fw_header *hdr, size_t len)
{
	u16 hdrsize;

	if (len < sizeof(*hdr))
		return "image too small";
	if (memcmp(hdr->hdr_vers, "HFW", 3) != 0)
		return "format not recognised";

	hdrsize = le16_to_cpu(hdr->headersize);
	if (hdrsize > len)
		return "bad headersize";
	if ((hdrsize + le32_to_cpu(hdr->block_offset)) > len)
		return "bad block offset";
	if ((hdrsize + le32_to_cpu(hdr->pdr_offset)) > len)
		return "bad PDR offset";
	if ((hdrsize + le32_to_cpu(hdr->pri_offset)) > len)
		return "bad PRI offset";
	if ((hdrsize + le32_to_cpu(hdr->compat_offset)) > len)
		return "bad compat offset";

	/* TODO: consider adding a checksum or CRC to the firmware format */
	return NULL;
}