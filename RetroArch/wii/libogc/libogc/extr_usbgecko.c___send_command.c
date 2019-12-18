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
typedef  int /*<<< orphan*/  u16 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXI_DEVICE_0 ; 
 int /*<<< orphan*/  EXI_Deselect (int) ; 
 int /*<<< orphan*/  EXI_Imm (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXI_READWRITE ; 
 int /*<<< orphan*/  EXI_SPEED32MHZ ; 
 int /*<<< orphan*/  EXI_Select (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXI_Sync (int) ; 

__attribute__((used)) static __inline__ int __send_command(s32 chn,u16 *cmd)
{
	s32 ret = 0;

	if(!EXI_Select(chn,EXI_DEVICE_0,EXI_SPEED32MHZ)) ret |= 0x01;
	if(!EXI_Imm(chn,cmd,sizeof(u16),EXI_READWRITE,NULL)) ret |= 0x02;
	if(!EXI_Sync(chn)) ret |= 0x04;
	if(!EXI_Deselect(chn)) ret |= 0x08;

	if(ret) return 0;
	return 1;
}