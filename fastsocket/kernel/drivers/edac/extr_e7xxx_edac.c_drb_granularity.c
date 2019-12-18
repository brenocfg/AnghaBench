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
typedef  int u32 ;

/* Variables and functions */
 int E7501 ; 

__attribute__((used)) static inline int drb_granularity(u32 drc, int dev_idx)
{
	/* only e7501 can be single channel */
	return (dev_idx == E7501) ? ((drc >> 18) & 0x3) : 1;
}