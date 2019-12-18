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
typedef  scalar_t__ cothread_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCE_SYSMODULE_FIBER ; 
 scalar_t__ co_active_ ; 
 int /*<<< orphan*/  sceSysmoduleLoadModule (int /*<<< orphan*/ ) ; 

cothread_t co_active(void)
{
   if(!co_active_)
   {
		  sceSysmoduleLoadModule(SCE_SYSMODULE_FIBER);
      co_active_ = (cothread_t)1;
   }
   return co_active_;
}