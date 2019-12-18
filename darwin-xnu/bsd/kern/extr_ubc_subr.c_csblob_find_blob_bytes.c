#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  magic; } ;
struct TYPE_6__ {TYPE_1__* index; int /*<<< orphan*/  count; } ;
struct TYPE_5__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ CS_SuperBlob ;
typedef  TYPE_3__ CS_GenericBlob ;

/* Variables and functions */
 scalar_t__ CSMAGIC_CODEDIRECTORY ; 
 scalar_t__ CSMAGIC_EMBEDDED_SIGNATURE ; 
 size_t CSSLOT_CODEDIRECTORY ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

const CS_GenericBlob *
csblob_find_blob_bytes(const uint8_t *addr, size_t length, uint32_t type, uint32_t magic)
{
	const CS_GenericBlob *blob = (const CS_GenericBlob *)(const void *)addr;

	if (ntohl(blob->magic) == CSMAGIC_EMBEDDED_SIGNATURE) {
		const CS_SuperBlob *sb = (const CS_SuperBlob *)blob;
		size_t n, count = ntohl(sb->count);

		for (n = 0; n < count; n++) {
			if (ntohl(sb->index[n].type) != type)
				continue;
			uint32_t offset = ntohl(sb->index[n].offset);
			if (length - sizeof(const CS_GenericBlob) < offset)
				return NULL;
			blob = (const CS_GenericBlob *)(const void *)(addr + offset);
			if (ntohl(blob->magic) != magic)
				continue;
			return blob;
		}
	} else if (type == CSSLOT_CODEDIRECTORY
		   && ntohl(blob->magic) == CSMAGIC_CODEDIRECTORY
		   && magic == CSMAGIC_CODEDIRECTORY)
		return blob;
	return NULL;
}