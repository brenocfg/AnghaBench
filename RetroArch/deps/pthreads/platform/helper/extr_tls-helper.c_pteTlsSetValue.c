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
 int /*<<< orphan*/  PTE_OS_INVALID_PARAM ; 
 int /*<<< orphan*/  PTE_OS_OK ; 

pte_osResult pteTlsSetValue(void *pTlsThreadStruct, unsigned int index, void * value)
{
   pte_osResult result;
   void ** pTls = (void **) pTlsThreadStruct;

   if (pTls != NULL)
   {
      pTls[index-1] = value;
      result = PTE_OS_OK;
   }
   else
      result = PTE_OS_INVALID_PARAM;

   return result;

}