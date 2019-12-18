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
struct qib_pportdata {int lflags; scalar_t__ lid; struct qib_devdata* dd; } ;
struct qib_devdata {int flags; scalar_t__ kregbase; } ;

/* Variables and functions */
 int QIBL_LINKACTIVE ; 
 int QIB_PRESENT ; 

__attribute__((used)) static inline int usable(struct qib_pportdata *ppd)
{
	struct qib_devdata *dd = ppd->dd;

	return dd && (dd->flags & QIB_PRESENT) && dd->kregbase && ppd->lid &&
		(ppd->lflags & QIBL_LINKACTIVE);
}