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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct qib_pportdata {TYPE_2__* cpspec; TYPE_1__* dd; } ;
struct TYPE_4__ {int /*<<< orphan*/ * cpregbase; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int QIB_PRESENT ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 read_7322_creg32_port(const struct qib_pportdata *ppd,
					u16 regno)
{
	if (!ppd->cpspec || !ppd->cpspec->cpregbase ||
	    !(ppd->dd->flags & QIB_PRESENT))
		return 0;
	return readl(&ppd->cpspec->cpregbase[regno]);
}