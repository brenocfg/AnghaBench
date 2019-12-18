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
struct ipath_devdata {int ipath_flags; } ;
typedef  int /*<<< orphan*/  ipath_kreg ;

/* Variables and functions */
 int IPATH_INTREG_64 ; 
 int /*<<< orphan*/  ipath_read_kreg32 (struct ipath_devdata const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_read_kreg64 (struct ipath_devdata const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 ipath_read_ireg(const struct ipath_devdata *dd, ipath_kreg r)
{
	return (dd->ipath_flags & IPATH_INTREG_64) ?
		ipath_read_kreg64(dd, r) : ipath_read_kreg32(dd, r);
}