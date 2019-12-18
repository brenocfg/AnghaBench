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
typedef  int /*<<< orphan*/  uint32_t ;
struct elfcopy {int s_cnt; int s_sn_sz; char* s_sn; char* as; int as_sz; scalar_t__* s_so; } ;

/* Variables and functions */
 size_t _ARHDR_LEN ; 
 size_t _ARMAG_LEN ; 
 scalar_t__ htobe32 (scalar_t__) ; 

__attribute__((used)) static void
sync_ar(struct elfcopy *ecp)
{
	size_t s_sz;		/* size of archive symbol table. */
	size_t pm_sz;		/* size of pseudo members */
	int i;

	/*
	 * Pad the symbol name string table. It is treated specially because
	 * symbol name table should be padded by a '\0', not the common '\n'
	 * for other members. The size of sn table includes the pad bit.
	 */
	if (ecp->s_cnt != 0 && ecp->s_sn_sz % 2 != 0)
		ecp->s_sn[ecp->s_sn_sz++] = '\0';

	/*
	 * Archive string table is padded by a "\n" as the normal members.
	 * The difference is that the size of archive string table counts
	 * in the pad bit, while normal members' size fileds do not.
	 */
	if (ecp->as != NULL && ecp->as_sz % 2 != 0)
		ecp->as[ecp->as_sz++] = '\n';

	/*
	 * If there is a symbol table, calculate the size of pseudo members,
	 * convert previously stored relative offsets to absolute ones, and
	 * then make them Big Endian.
	 *
	 * absolute_offset = htobe32(relative_offset + size_of_pseudo_members)
	 */

	if (ecp->s_cnt != 0) {
		s_sz = (ecp->s_cnt + 1) * sizeof(uint32_t) + ecp->s_sn_sz;
		pm_sz = _ARMAG_LEN + (_ARHDR_LEN + s_sz);
		if (ecp->as != NULL)
			pm_sz += _ARHDR_LEN + ecp->as_sz;
		for (i = 0; (size_t)i < ecp->s_cnt; i++)
			*(ecp->s_so + i) = htobe32(*(ecp->s_so + i) +
			    pm_sz);
	}
}