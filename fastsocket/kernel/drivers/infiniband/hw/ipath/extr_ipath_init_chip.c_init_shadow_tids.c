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
struct page {int dummy; } ;
struct ipath_devdata {int ipath_cfgports; int ipath_rcvtidcnt; int /*<<< orphan*/ * ipath_physshadow; struct page** ipath_pageshadow; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*) ; 
 int /*<<< orphan*/  vfree (struct page**) ; 
 int /*<<< orphan*/ * vmalloc (int) ; 
 struct page** vzalloc (int) ; 

__attribute__((used)) static void init_shadow_tids(struct ipath_devdata *dd)
{
	struct page **pages;
	dma_addr_t *addrs;

	pages = vzalloc(dd->ipath_cfgports * dd->ipath_rcvtidcnt *
			sizeof(struct page *));
	if (!pages) {
		ipath_dev_err(dd, "failed to allocate shadow page * "
			      "array, no expected sends!\n");
		dd->ipath_pageshadow = NULL;
		return;
	}

	addrs = vmalloc(dd->ipath_cfgports * dd->ipath_rcvtidcnt *
			sizeof(dma_addr_t));
	if (!addrs) {
		ipath_dev_err(dd, "failed to allocate shadow dma handle "
			      "array, no expected sends!\n");
		vfree(pages);
		dd->ipath_pageshadow = NULL;
		return;
	}

	dd->ipath_pageshadow = pages;
	dd->ipath_physshadow = addrs;
}