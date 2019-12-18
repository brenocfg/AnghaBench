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
typedef  int u16 ;

/* Variables and functions */
 int QMAP_IDX_MASK ; 

__attribute__((used)) static u64 replace_wr_id(u64 wr_id, u16 idx)
{
	u64 ret;

	ret = wr_id & ~QMAP_IDX_MASK;
	ret |= idx & QMAP_IDX_MASK;

	return ret;
}