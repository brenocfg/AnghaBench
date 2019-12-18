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
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 TYPE_1__* __dvd_executing ; 
 int /*<<< orphan*/  __dvd_statecoverclosed () ; 
 scalar_t__* _diReg ; 

__attribute__((used)) static void __dvd_statemotorstoppedcb(s32 result)
{
	_diReg[1] = 0;
	__dvd_executing->state = 3;
	__dvd_statecoverclosed();
}