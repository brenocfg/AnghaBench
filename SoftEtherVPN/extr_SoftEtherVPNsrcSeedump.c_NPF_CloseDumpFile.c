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
typedef  int /*<<< orphan*/  POPEN_INSTANCE ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS NPF_CloseDumpFile(POPEN_INSTANCE Open){
#if 0
    IF_LOUD(DbgPrint("NPF: NPF_CloseDumpFile.\n");)
    IF_LOUD(DbgPrint("Dumpoffset=%d\n",Open->DumpOffset.QuadPart);)

DbgPrint("1\n");
   // Consistency check
   if(Open->DumpFileHandle == NULL)
      return STATUS_UNSUCCESSFUL;

DbgPrint("2\n");
   ZwClose( Open->DumpFileHandle );

   ObDereferenceObject(Open->DumpFileObject);
/*
   if(Open->DumpLimitReached == TRUE)
      // Limit already reached: don't save the rest of the buffer.
      return STATUS_SUCCESS;
*/
DbgPrint("3\n");

   NPF_OpenDumpFile(Open,&Open->DumpFileName, TRUE);

   // Flush the buffer to file 
   NPF_SaveCurrentBuffer(Open);

   // Close The file
   ObDereferenceObject(Open->DumpFileObject);
   ZwClose( Open->DumpFileHandle );
   
   Open->DumpFileHandle = NULL;

   ObDereferenceObject(Open->DumpFileObject);
#endif
   return STATUS_SUCCESS;
}