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
typedef  int /*<<< orphan*/  semName ;
typedef  int /*<<< orphan*/  pte_osSemaphoreHandle ;
typedef  int /*<<< orphan*/  pte_osResult ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PSP_UID ; 
 int /*<<< orphan*/  PTE_OS_OK ; 
 int /*<<< orphan*/  SEM_VALUE_MAX ; 
 int /*<<< orphan*/  sceKernelCreateSema (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

pte_osResult pte_osSemaphoreCreate(int initialValue, pte_osSemaphoreHandle *pHandle)
{
   pte_osSemaphoreHandle handle;
   static int semCtr = 0;
   char semName[32];

   if (semCtr++ > MAX_PSP_UID)
      semCtr = 0;

   snprintf(semName,sizeof(semName),"pthread_sem%d",semCtr);

   handle = sceKernelCreateSema(semName,
         0,              /* attributes (default) */
         initialValue,   /* initial value        */
         SEM_VALUE_MAX,  /* maximum value        */
         0);             /* options (default)    */

   *pHandle = handle;

   return PTE_OS_OK;
}