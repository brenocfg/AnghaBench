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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ehca_mr_pginfo {int type; int /*<<< orphan*/  hwpage_size; } ;

/* Variables and functions */
 int EFAULT ; 
#define  EHCA_MR_PGI_FMR 130 
#define  EHCA_MR_PGI_PHYS 129 
#define  EHCA_MR_PGI_USER 128 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  ehca_gen_err (char*,int) ; 
 int ehca_set_pagebuf_fmr (struct ehca_mr_pginfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ehca_set_pagebuf_phys (struct ehca_mr_pginfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ehca_set_pagebuf_user1 (struct ehca_mr_pginfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ehca_set_pagebuf_user2 (struct ehca_mr_pginfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ehca_set_pagebuf(struct ehca_mr_pginfo *pginfo,
		     u32 number,
		     u64 *kpage)
{
	int ret;

	switch (pginfo->type) {
	case EHCA_MR_PGI_PHYS:
		ret = ehca_set_pagebuf_phys(pginfo, number, kpage);
		break;
	case EHCA_MR_PGI_USER:
		ret = PAGE_SIZE >= pginfo->hwpage_size ?
			ehca_set_pagebuf_user1(pginfo, number, kpage) :
			ehca_set_pagebuf_user2(pginfo, number, kpage);
		break;
	case EHCA_MR_PGI_FMR:
		ret = ehca_set_pagebuf_fmr(pginfo, number, kpage);
		break;
	default:
		ehca_gen_err("bad pginfo->type=%x", pginfo->type);
		ret = -EFAULT;
		break;
	}
	return ret;
}