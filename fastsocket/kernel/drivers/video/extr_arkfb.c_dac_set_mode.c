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
struct dac_info {TYPE_1__* dacops; } ;
struct TYPE_2__ {int (* dac_set_mode ) (struct dac_info*,int) ;} ;

/* Variables and functions */
 int stub1 (struct dac_info*,int) ; 

__attribute__((used)) static inline int dac_set_mode(struct dac_info *info, int mode)
{
	return info->dacops->dac_set_mode(info, mode);
}