#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ehca_shca {int dummy; } ;
struct ehca_mr_pginfo {int dummy; } ;
struct ehca_mr {int dummy; } ;
struct TYPE_4__ {TYPE_1__** top; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dir; } ;

/* Variables and functions */
 int EHCA_MAP_ENTRIES ; 
 scalar_t__ H_PAGE_REGISTERED ; 
 scalar_t__ H_SUCCESS ; 
 TYPE_2__* ehca_bmap ; 
 int /*<<< orphan*/  ehca_bmap_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ ehca_reg_mr_sections (int,int,scalar_t__*,struct ehca_shca*,struct ehca_mr*,struct ehca_mr_pginfo*) ; 

__attribute__((used)) static u64 ehca_reg_mr_dir_sections(int top, u64 *kpage, struct ehca_shca *shca,
				    struct ehca_mr *mr,
				    struct ehca_mr_pginfo *pginfo)
{
	u64 hret = H_SUCCESS;
	int dir;

	for (dir = 0; dir < EHCA_MAP_ENTRIES; dir++) {
		if (!ehca_bmap_valid(ehca_bmap->top[top]->dir[dir]))
			continue;

		hret = ehca_reg_mr_sections(top, dir, kpage, shca, mr, pginfo);
		if ((hret != H_SUCCESS) && (hret != H_PAGE_REGISTERED))
				return hret;
	}
	return hret;
}