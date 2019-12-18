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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u16 ;
struct qib_devdata {int flags; TYPE_1__* cspec; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cregbase; } ;

/* Variables and functions */
 int QIB_PRESENT ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void write_7220_creg(const struct qib_devdata *dd,
				   u16 regno, u64 value)
{
	if (dd->cspec->cregbase && (dd->flags & QIB_PRESENT))
		writeq(value, &dd->cspec->cregbase[regno]);
}