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
typedef  scalar_t__ u16 ;
struct ipath_devdata {int /*<<< orphan*/  ipath_sdma_desc_nreserved; } ;

/* Variables and functions */

__attribute__((used)) static inline void ipath_sdma_desc_reserve(struct ipath_devdata *dd, u16 cnt)
{
	dd->ipath_sdma_desc_nreserved += cnt;
}