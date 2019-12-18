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
struct ipath_devdata {int /*<<< orphan*/ * ipath_kregbase; } ;
typedef  size_t ipath_kreg ;

/* Variables and functions */
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ipath_write_kreg(const struct ipath_devdata *dd,
				    ipath_kreg regno, u64 value)
{
	if (dd->ipath_kregbase)
		writeq(value, &dd->ipath_kregbase[regno]);
}