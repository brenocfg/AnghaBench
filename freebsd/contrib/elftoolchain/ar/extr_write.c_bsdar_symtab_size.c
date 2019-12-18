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
struct bsdar {int options; int s_cnt; int s_sn_sz; } ;

/* Variables and functions */
 int AR_BSD ; 

__attribute__((used)) static size_t
bsdar_symtab_size(struct bsdar *bsdar)
{
	size_t sz;

	if (bsdar->options & AR_BSD) {
		/*
		 * A BSD style symbol table has two parts.
		 * Each part is preceded by its size in bytes,
		 * encoded as a C 'long'.  In the first part,
		 * there are 's_cnt' entries, each entry being
		 * 2 'long's in size.  The second part
		 * contains a string table.
		 */
		sz = 2 * sizeof(long) + (bsdar->s_cnt * 2 * sizeof(long)) +
		    bsdar->s_sn_sz;
	} else {
		/*
		 * An SVR4 style symbol table comprises of a 32 bit
		 * number holding the number of entries, followed by
		 * that many 32-bit offsets, followed by a string
		 * table.
		 */
		sz = sizeof(uint32_t) + bsdar->s_cnt * sizeof(uint32_t) +
		    bsdar->s_sn_sz;
	}

	return (sz);
}