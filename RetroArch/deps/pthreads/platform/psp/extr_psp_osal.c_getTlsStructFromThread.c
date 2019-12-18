#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  SceUID ;
typedef  TYPE_1__ SceKernelThreadInfo ;

/* Variables and functions */
 void* globalTls ; 
 int /*<<< orphan*/  sceKernelReferThreadStatus (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sscanf (int /*<<< orphan*/ ,char*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void *getTlsStructFromThread(SceUID thid)
{
   SceKernelThreadInfo thinfo;
   unsigned int ptr;
   unsigned int thrNum;
   int numMatches;

   thinfo.size = sizeof(SceKernelThreadInfo);

   sceKernelReferThreadStatus(thid, &thinfo);

   numMatches = sscanf(thinfo.name,"pthread%04d__%x", &thrNum, &ptr);

   /* If we were called from a pthread, use the TLS allocated when the thread
    * was created.  Otherwise, we were called from a non-pthread, so use the
    * "global".  This is a pretty bad hack, but necessary due to lack of TLS on PSP.
    */
   if (numMatches == 2)
      return (void *) ptr;

   return globalTls;
}