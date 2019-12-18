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
 int /*<<< orphan*/  SCE_SYSMODULE_FIBER ; 
 int _sceFiberInitializeImpl (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ co_active_ ; 
 int /*<<< orphan*/  co_thunk ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  sceSysmoduleLoadModule (int /*<<< orphan*/ ) ; 

cothread_t co_create(unsigned int heapsize, void (*coentry)(void))
{
   SceFiber* tailFiber = malloc(sizeof(SceFiber));
	 char * m_contextBuffer = malloc(sizeof(char)*heapsize);
	 if(!co_active_)
   {
      sceSysmoduleLoadModule(SCE_SYSMODULE_FIBER);
      co_active_ = (cothread_t)1;
   }

   //_sceFiberInitializeImpl
   int ret = _sceFiberInitializeImpl(tailFiber, "tailFiber", co_thunk, (uint32_t)coentry, (void*) m_contextBuffer, heapsize, NULL);
   if(ret==0){
     return (cothread_t)tailFiber;
   }else{
     return (cothread_t)ret;
   }

}