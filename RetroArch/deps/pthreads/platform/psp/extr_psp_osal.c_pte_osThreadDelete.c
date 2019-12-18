#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pte_osThreadHandle ;
typedef  int /*<<< orphan*/  pte_osResult ;
struct TYPE_4__ {int /*<<< orphan*/  cancelSem; } ;
typedef  TYPE_1__ pspThreadData ;

/* Variables and functions */
 int /*<<< orphan*/  PTE_OS_OK ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* getThreadData (int /*<<< orphan*/ ) ; 
 void* getTlsStructFromThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pteTlsThreadDestroy (void*) ; 
 int /*<<< orphan*/  sceKernelDeleteSema (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceKernelDeleteThread (int /*<<< orphan*/ ) ; 

pte_osResult pte_osThreadDelete(pte_osThreadHandle handle)
{
   void                 *pTls = getTlsStructFromThread(handle);
   pspThreadData *pThreadData = getThreadData(handle);

   sceKernelDeleteSema(pThreadData->cancelSem);  

   free(pThreadData);

   pteTlsThreadDestroy(pTls);

   sceKernelDeleteThread(handle);

   return PTE_OS_OK;
}