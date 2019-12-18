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
typedef  int /*<<< orphan*/  u32 ;
struct mthca_mr {int /*<<< orphan*/ * mtt; } ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int mthca_mr_alloc (struct mthca_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,struct mthca_mr*) ; 

int mthca_mr_alloc_notrans(struct mthca_dev *dev, u32 pd,
			   u32 access, struct mthca_mr *mr)
{
	mr->mtt = NULL;
	return mthca_mr_alloc(dev, pd, 12, 0, ~0ULL, access, mr);
}