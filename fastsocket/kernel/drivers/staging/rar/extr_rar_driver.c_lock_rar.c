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
typedef  int u32 ;
struct TYPE_2__ {int low; } ;

/* Variables and functions */
 int ENODEV ; 
 int memrar_set_rar_addr (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* rar_addr ; 
 int /*<<< orphan*/  rar_dev ; 
 scalar_t__ registered ; 

int lock_rar(int rar_index)
{
	u32 working_addr;
	int result;
if (registered && (rar_index < 3) && (rar_index >= 0)) {
	/* first make sure that lock bits are clear (this does lock) */
	working_addr=rar_addr[rar_index].low & 0xfffffff0;

	/* now send that value to the register using the IPC */
        result=memrar_set_rar_addr(rar_dev,rar_index,working_addr);
	return result;
	}

else {
	return -ENODEV;
	}
}