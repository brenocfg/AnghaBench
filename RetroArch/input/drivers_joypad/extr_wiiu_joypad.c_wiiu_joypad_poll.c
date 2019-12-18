#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* poll ) () ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* poll ) () ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* poll ) () ;} ;

/* Variables and functions */
 TYPE_3__ hidpad_driver ; 
 TYPE_2__ kpad_driver ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 () ; 
 TYPE_1__ wpad_driver ; 

__attribute__((used)) static void wiiu_joypad_poll(void)
{
   wpad_driver.poll();
   kpad_driver.poll();
#ifdef WIIU_HID
   hidpad_driver.poll();
#endif
}