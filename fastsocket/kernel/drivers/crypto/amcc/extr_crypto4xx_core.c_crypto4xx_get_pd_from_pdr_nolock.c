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
struct crypto4xx_device {int pdr_head; int pdr_tail; } ;

/* Variables and functions */
 int ERING_WAS_FULL ; 
 int PPC4XX_NUM_PD ; 

__attribute__((used)) static u32 crypto4xx_get_pd_from_pdr_nolock(struct crypto4xx_device *dev)
{
	u32 retval;
	u32 tmp;

	retval = dev->pdr_head;
	tmp = (dev->pdr_head + 1) % PPC4XX_NUM_PD;

	if (tmp == dev->pdr_tail)
		return ERING_WAS_FULL;

	dev->pdr_head = tmp;

	return retval;
}