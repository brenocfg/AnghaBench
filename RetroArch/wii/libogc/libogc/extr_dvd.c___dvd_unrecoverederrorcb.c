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
typedef  int s32 ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVD_LowRequestError (int /*<<< orphan*/ ) ; 
 TYPE_1__* __dvd_executing ; 
 int /*<<< orphan*/  __dvd_stategotoretry () ; 
 int /*<<< orphan*/  __dvd_statetimeout () ; 
 int /*<<< orphan*/  __dvd_unrecoverederrorretrycb ; 

__attribute__((used)) static void __dvd_unrecoverederrorcb(s32 result)
{
	if(result==0x0010) {
		__dvd_executing->state = -1;
		__dvd_statetimeout();
		return;
	}
	if(result&0x0001) {
		__dvd_stategotoretry();
		return;
	}
	if(!(result==0x0002)) DVD_LowRequestError(__dvd_unrecoverederrorretrycb);
}