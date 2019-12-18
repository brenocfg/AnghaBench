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
struct net_device {int dummy; } ;

/* Variables and functions */
 int BIT30 ; 
 int BIT31 ; 
 int /*<<< orphan*/  CAM_empty_entry (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  CAM_mark_invalid (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  RWCAM ; 
 scalar_t__ TOTAL_CAM_ENTRY ; 
 scalar_t__ ucIndex ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int) ; 

void CamResetAllEntry(struct net_device *dev)
{
	//u8 ucIndex;
	u32 ulcommand = 0;

#if 1
	ulcommand |= BIT31|BIT30;
	write_nic_dword(dev, RWCAM, ulcommand);
#else
        for(ucIndex=0;ucIndex<TOTAL_CAM_ENTRY;ucIndex++)
                CAM_mark_invalid(dev, ucIndex);
        for(ucIndex=0;ucIndex<TOTAL_CAM_ENTRY;ucIndex++)
                CAM_empty_entry(dev, ucIndex);
#endif
}