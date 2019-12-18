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
struct dump_hdr_s390 {unsigned int cpu_cnt; int /*<<< orphan*/ * lc_vec; int /*<<< orphan*/  real_cpu_cnt; } ;
struct dump_hdr_lkcd_asm {int hdr_size; unsigned int cpu_cnt; int /*<<< orphan*/ * lc_vec; int /*<<< orphan*/  real_cpu_cnt; scalar_t__ version; int /*<<< orphan*/  magic_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_MAGIC_NUMBER_ASM ; 

__attribute__((used)) static void s390_to_lkcd_hdr_asm(struct dump_hdr_s390 *s390_dh,
			         struct dump_hdr_lkcd_asm *dh_asm)
{
	unsigned int i;

	dh_asm->magic_number = DUMP_MAGIC_NUMBER_ASM;
	dh_asm->version = 0;
	dh_asm->hdr_size = sizeof(*dh_asm);
	dh_asm->cpu_cnt = s390_dh->cpu_cnt;
	dh_asm->real_cpu_cnt = s390_dh->real_cpu_cnt;
	for (i = 0; i < dh_asm->cpu_cnt; i++)
		dh_asm->lc_vec[i] = s390_dh->lc_vec[i];
}