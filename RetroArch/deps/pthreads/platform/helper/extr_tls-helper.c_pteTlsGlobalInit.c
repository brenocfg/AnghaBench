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
typedef  int /*<<< orphan*/  pte_osResult ;

/* Variables and functions */
 int /*<<< orphan*/  PTE_OS_NO_RESOURCES ; 
 int /*<<< orphan*/  PTE_OS_OK ; 
 int /*<<< orphan*/  globalTlsLock ; 
 int* keysUsed ; 
 scalar_t__ malloc (int) ; 
 int maxTlsValues ; 
 int /*<<< orphan*/  pte_osMutexCreate (int /*<<< orphan*/ *) ; 

pte_osResult pteTlsGlobalInit(int maxEntries)
{
   int i;
   pte_osResult result;

   pte_osMutexCreate(&globalTlsLock);

   keysUsed = (int *) malloc(maxEntries * sizeof(int));

   if (keysUsed != NULL)
   {
      for (i=0;i<maxEntries;i++)
         keysUsed[i] = 0;

      maxTlsValues = maxEntries;

      result = PTE_OS_OK;
   }
   else
      result = PTE_OS_NO_RESOURCES;

   return result;
}