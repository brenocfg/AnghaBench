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

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int maxTlsValues ; 

void * pteTlsThreadInit(void)
{
   int i;
   void **pTlsStruct = (void **) malloc(maxTlsValues * sizeof(void*));

   /* PTE library assumes that keys are initialized to zero */
   for (i=0; i<maxTlsValues;i++)
      pTlsStruct[i] = 0;

   return (void *) pTlsStruct;
}