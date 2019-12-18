#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  dvderr_code; } ;
typedef  TYPE_1__ syssramex ;

/* Variables and functions */
 TYPE_1__* __SYS_LockSramEx () ; 
 int /*<<< orphan*/  __SYS_UnlockSramEx (int) ; 
 int /*<<< orphan*/  convert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __dvd_storeerror(u32 errorcode)
{
	u8 err;
	syssramex *ptr;

	err = convert(errorcode);
	ptr = __SYS_LockSramEx();
	ptr->dvderr_code = err;
	__SYS_UnlockSramEx(1);
}