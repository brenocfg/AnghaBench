#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ushort_t ;
struct TYPE_5__ {scalar_t__ ctt_size; scalar_t__ ctt_info; int /*<<< orphan*/  ctt_name; int /*<<< orphan*/  ctt_lsizelo; int /*<<< orphan*/  ctt_lsizehi; } ;
typedef  TYPE_1__ ctf_type_t ;
typedef  TYPE_1__ ctf_stype_t ;
typedef  int /*<<< orphan*/  ctf_buf_t ;

/* Variables and functions */
 scalar_t__ CTF_LSIZE_SENT ; 
 size_t CTF_MAX_SIZE ; 
 int /*<<< orphan*/  CTF_SIZE_TO_LSIZE_HI (size_t) ; 
 int /*<<< orphan*/  CTF_SIZE_TO_LSIZE_LO (size_t) ; 
 int /*<<< orphan*/  SWAP_16 (scalar_t__) ; 
 int /*<<< orphan*/  SWAP_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_buf_write (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ target_requires_swap ; 

__attribute__((used)) static void
write_sized_type_rec(ctf_buf_t *b, ctf_type_t *ctt, size_t size)
{
	if (size > CTF_MAX_SIZE) {
		ctt->ctt_size = CTF_LSIZE_SENT;
		ctt->ctt_lsizehi = CTF_SIZE_TO_LSIZE_HI(size);
		ctt->ctt_lsizelo = CTF_SIZE_TO_LSIZE_LO(size);
		if (target_requires_swap) {
			SWAP_32(ctt->ctt_name);
			SWAP_16(ctt->ctt_info);
			SWAP_16(ctt->ctt_size);
			SWAP_32(ctt->ctt_lsizehi);
			SWAP_32(ctt->ctt_lsizelo);
		}
		ctf_buf_write(b, ctt, sizeof (*ctt));
	} else {
		ctf_stype_t *cts = (ctf_stype_t *)ctt;

		cts->ctt_size = (ushort_t)size;

		if (target_requires_swap) {
			SWAP_32(cts->ctt_name);
			SWAP_16(cts->ctt_info);
			SWAP_16(cts->ctt_size);
		}

		ctf_buf_write(b, cts, sizeof (*cts));
	}
}