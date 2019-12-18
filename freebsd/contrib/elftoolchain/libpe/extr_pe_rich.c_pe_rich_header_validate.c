#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {char* pe_rh_start; char* pe_stub; TYPE_1__* pe_rh; } ;
struct TYPE_5__ {scalar_t__ rh_total; unsigned char* rh_compid; int* rh_cnt; scalar_t__ rh_xor; } ;
typedef  TYPE_1__ PE_RichHdr ;
typedef  TYPE_2__ PE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pe_rich_header (TYPE_2__*) ; 
 scalar_t__ rol32 (unsigned char,int) ; 

int
pe_rich_header_validate(PE *pe)
{
	PE_RichHdr *rh;
	uint32_t cksum;
	char *p;
	int i, off;

	if (pe_rich_header(pe) == NULL)
		return (-1);

	assert(pe->pe_rh_start != NULL);

	/*
	 * Initial value of the checksum is the offset to the begin of
	 * the Rich header.
	 */
	cksum = pe->pe_rh_start - pe->pe_stub;

	/*
	 * Add the bytes before the Rich header to the checksum, rotated
	 * left by the offset.
	 */
	for (p = pe->pe_stub; p < pe->pe_rh_start; p++) {
		/* Skip dh_lfanew. */
		off = p - pe->pe_stub;
		if (off >= 0x3c && off < 0x40)
			continue;
		cksum += rol32((unsigned char) *p, off);
	}

	/* Add each compid rotated left by its count to the checksum. */
	rh = pe->pe_rh;
	for (i = 0; (uint32_t) i < rh->rh_total; i++)
		cksum += rol32(rh->rh_compid[i], rh->rh_cnt[i]);

	/* Validate the checksum with the XOR mask stored after "Rich". */
	if (cksum == rh->rh_xor)
		return (1);

	return (0);
}