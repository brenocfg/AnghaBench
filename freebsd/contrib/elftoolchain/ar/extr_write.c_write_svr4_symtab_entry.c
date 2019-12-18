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
typedef  size_t uint32_t ;
struct bsdar {size_t s_cnt; size_t* s_so; int* s_sn; int s_sn_sz; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 void* htobe32 (size_t) ; 
 int /*<<< orphan*/  write_data (struct bsdar*,struct archive*,int*,int) ; 

__attribute__((used)) static void
write_svr4_symtab_entry(struct bsdar *bsdar, struct archive *a)
{
	int		nr;
	uint32_t	i;

	/* Translate offsets to big-endian form. */
	for (i = 0; i < bsdar->s_cnt; i++)
		bsdar->s_so[i] = htobe32(bsdar->s_so[i]);

	nr = htobe32(bsdar->s_cnt);
	write_data(bsdar, a, &nr, sizeof(uint32_t));
	write_data(bsdar, a, bsdar->s_so, sizeof(uint32_t) *
	    bsdar->s_cnt);
	write_data(bsdar, a, bsdar->s_sn, bsdar->s_sn_sz);
}