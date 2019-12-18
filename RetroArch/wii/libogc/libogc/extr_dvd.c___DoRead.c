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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  dvdcallbacklow ;
struct TYPE_2__ {int cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  __Read (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* __dvd_cmdlist ; 
 scalar_t__ __dvd_nextcmdnum ; 

__attribute__((used)) static void __DoRead(void *buffer,u32 len,s64 offset,dvdcallbacklow cb)
{
	__dvd_nextcmdnum = 0;
	__dvd_cmdlist[0].cmd = -1;
	__Read(buffer,len,offset,cb);
}