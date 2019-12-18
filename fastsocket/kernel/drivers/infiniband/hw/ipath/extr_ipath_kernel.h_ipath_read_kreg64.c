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
typedef  int u64 ;
struct ipath_devdata {int ipath_flags; int /*<<< orphan*/ * ipath_kregbase; } ;
typedef  size_t ipath_kreg ;

/* Variables and functions */
 int IPATH_PRESENT ; 
 int readq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u64 ipath_read_kreg64(const struct ipath_devdata *dd,
				    ipath_kreg regno)
{
	if (!dd->ipath_kregbase || !(dd->ipath_flags & IPATH_PRESENT))
		return -1;

	return readq(&dd->ipath_kregbase[regno]);
}