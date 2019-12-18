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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ cothread_t ;
typedef  int /*<<< orphan*/  SceFiber ;

/* Variables and functions */
 scalar_t__ co_active_ ; 
 int /*<<< orphan*/  sceFiberReturnToThread (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sceFiberRun (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sceFiberSwitch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void co_switch(cothread_t cothread)
{

   uint32_t argOnReturn = 0;
   if(cothread == (cothread_t)1){
     co_active_ = cothread;
     sceFiberReturnToThread(0, NULL);
   }else{
		 SceFiber* theFiber = (SceFiber*)cothread;
		 if(co_active_ == (cothread_t)1){
			 co_active_ = cothread;
			 sceFiberRun(theFiber, 0, &argOnReturn);
		 }else{
			 co_active_ = cothread;
			 sceFiberSwitch(theFiber, 0, &argOnReturn);
		 }
   }
}