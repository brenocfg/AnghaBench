#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ib_mr {int dummy; } ;
struct TYPE_2__ {int access_flags; } ;
struct ipath_mr {struct ib_mr ibmr; TYPE_1__ mr; } ;
struct ib_pd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ib_mr* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ipath_mr* kzalloc (int,int /*<<< orphan*/ ) ; 

struct ib_mr *ipath_get_dma_mr(struct ib_pd *pd, int acc)
{
	struct ipath_mr *mr;
	struct ib_mr *ret;

	mr = kzalloc(sizeof *mr, GFP_KERNEL);
	if (!mr) {
		ret = ERR_PTR(-ENOMEM);
		goto bail;
	}

	mr->mr.access_flags = acc;
	ret = &mr->ibmr;

bail:
	return ret;
}