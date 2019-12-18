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
typedef  int /*<<< orphan*/  u32 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXI_GetID (int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 __unlocked_handler(s32 nChn,s32 nDev)
{
	u32 nId;
	EXI_GetID(nChn,nDev,&nId);
	return 1;
}