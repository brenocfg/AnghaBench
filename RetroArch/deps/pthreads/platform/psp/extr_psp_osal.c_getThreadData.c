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
typedef  int /*<<< orphan*/  pspThreadData ;
typedef  int /*<<< orphan*/  SceUID ;

/* Variables and functions */
 void* getTlsStructFromThread (int /*<<< orphan*/ ) ; 
 scalar_t__ pteTlsGetValue (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  threadDataKey ; 

__attribute__((used)) static pspThreadData *getThreadData(SceUID threadHandle)
{
   void *pTls = getTlsStructFromThread(threadHandle);
   pspThreadData *pThreadData = (pspThreadData *)
      pteTlsGetValue(pTls, threadDataKey);

   return pThreadData;
}