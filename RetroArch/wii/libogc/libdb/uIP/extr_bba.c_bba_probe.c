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
typedef  scalar_t__ u32 ;
struct uip_netif {int dummy; } ;
typedef  int s8_t ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ BBA_CID ; 
 int /*<<< orphan*/  EXI_CHANNEL_0 ; 
 int /*<<< orphan*/  EXI_DEVICE_2 ; 
 scalar_t__ EXI_Lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXI_Unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ __bba_read_cid () ; 
 int bba_init_one (struct uip_netif*) ; 

__attribute__((used)) static s8_t bba_probe(struct uip_netif *dev)
{
	s32 ret;
	u32 cid;

	if(EXI_Lock(EXI_CHANNEL_0,EXI_DEVICE_2,NULL)==0) return -1;

	cid = __bba_read_cid();
	if(cid!=BBA_CID) {
		EXI_Unlock(EXI_CHANNEL_0);
		return -1;
	}

	ret = bba_init_one(dev);

	EXI_Unlock(EXI_CHANNEL_0);
	return ret;
}