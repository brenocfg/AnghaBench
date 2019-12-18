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
struct TYPE_2__ {int tpt_top; int tpt_base; } ;
struct cxio_rdev {TYPE_1__ rnic_info; } ;

/* Variables and functions */
 scalar_t__ T3_MAX_NUM_STAG ; 
 int min (int,int) ; 

__attribute__((used)) static inline int cxio_num_stags(struct cxio_rdev *rdev_p)
{
	return min((int)T3_MAX_NUM_STAG, (int)((rdev_p->rnic_info.tpt_top - rdev_p->rnic_info.tpt_base) >> 5));
}