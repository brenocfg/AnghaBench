#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sf_pkthdr {scalar_t__ caplen; } ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  Status; } ;
struct TYPE_7__ {scalar_t__ QuadPart; } ;
struct TYPE_6__ {scalar_t__ Bhead; scalar_t__ Btail; scalar_t__ BLastByte; scalar_t__ Buffer; scalar_t__ MaxDumpBytes; TYPE_2__ DumpOffset; int /*<<< orphan*/  ReadEvent; void* DumpLimitReached; int /*<<< orphan*/  DumpFileObject; } ;
typedef  TYPE_1__* POPEN_INSTANCE ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ CurrBuff ; 
 int /*<<< orphan*/  DbgPrint (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IF_LOUD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * IoAllocateMdl (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoFreeMdl (int /*<<< orphan*/ *) ; 
 TYPE_3__ IoStatus ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MmBuildMdlForNonPagedPool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NPF_WriteDumpFile (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 scalar_t__ SizeToDump ; 
 scalar_t__ TLastByte ; 
 void* TRUE ; 
 scalar_t__ Thead ; 
 scalar_t__ Ttail ; 
 int /*<<< orphan*/ * lMdl ; 

NTSTATUS NPF_SaveCurrentBuffer(POPEN_INSTANCE Open)
{
#if 0

   Thead=Open->Bhead;
   Ttail=Open->Btail;
   TLastByte=Open->BLastByte;
   
    IF_LOUD(DbgPrint("NPF: NPF_SaveCurrentBuffer.\n");)

   // Get the address of the buffer
   CurrBuff=Open->Buffer;
   //
   // Fill the application buffer
   //
   if( Ttail < Thead )
   {
      if(Open->MaxDumpBytes &&
         (UINT)Open->DumpOffset.QuadPart /*+ GetBuffOccupation(Open)*/ > Open->MaxDumpBytes)
      {
         // Size limit reached
         UINT PktLen;
         
         SizeToDump = 0;
         
         // Scan the buffer to detect the exact amount of data to save
         while(TRUE){
            PktLen = ((struct sf_pkthdr*)(CurrBuff + Thead + SizeToDump))->caplen + sizeof(struct sf_pkthdr);
            
            if((UINT)Open->DumpOffset.QuadPart + SizeToDump + PktLen > Open->MaxDumpBytes)
               break;
            
            SizeToDump += PktLen;
         }
         
      }
      else
         SizeToDump = TLastByte-Thead;
      
      lMdl=IoAllocateMdl(CurrBuff+Thead, SizeToDump, FALSE, FALSE, NULL);
      if (lMdl == NULL)
      {
         // No memory: stop dump
         IF_LOUD(DbgPrint("NPF: dump thread: Failed to allocate Mdl\n");)
         return STATUS_UNSUCCESSFUL;
      }
      
      MmBuildMdlForNonPagedPool(lMdl);
      
      // Write to disk
      NPF_WriteDumpFile(Open->DumpFileObject,
         &Open->DumpOffset,
         SizeToDump,
         lMdl,
         &IoStatus);
      
      IoFreeMdl(lMdl);
      
      if(!NT_SUCCESS(IoStatus.Status)){
         // Error
         return STATUS_UNSUCCESSFUL;
      }
      
      if(SizeToDump != TLastByte-Thead){
         // Size limit reached.
         Open->DumpLimitReached = TRUE;
   
         // Awake the application
         KeSetEvent(Open->ReadEvent,0,FALSE);

         return STATUS_UNSUCCESSFUL;
      }
      
      // Update the packet buffer
      Open->DumpOffset.QuadPart+=(TLastByte-Thead);
      Open->BLastByte=Ttail;
      Open->Bhead=0;
   }

   if( Ttail > Thead ){
      
      if(Open->MaxDumpBytes &&
         (UINT)Open->DumpOffset.QuadPart /* +GetBuffOccupation(Open)*/ > Open->MaxDumpBytes)
      {
         // Size limit reached
         UINT PktLen;
                  
         SizeToDump = 0;
         
         // Scan the buffer to detect the exact amount of data to save
         while(Thead + SizeToDump < Ttail){

            PktLen = ((struct sf_pkthdr*)(CurrBuff + Thead + SizeToDump))->caplen + sizeof(struct sf_pkthdr);
            
            if((UINT)Open->DumpOffset.QuadPart + SizeToDump + PktLen > Open->MaxDumpBytes)
               break;
            
            SizeToDump += PktLen;
         }
         
      }
      else
         SizeToDump = Ttail-Thead;
            
      lMdl=IoAllocateMdl(CurrBuff+Thead, SizeToDump, FALSE, FALSE, NULL);
      if (lMdl == NULL)
      {
         // No memory: stop dump
         IF_LOUD(DbgPrint("NPF: dump thread: Failed to allocate Mdl\n");)
         return STATUS_UNSUCCESSFUL;
      }
      
      MmBuildMdlForNonPagedPool(lMdl);
      
      // Write to disk
      NPF_WriteDumpFile(Open->DumpFileObject,
         &Open->DumpOffset,
         SizeToDump,
         lMdl,
         &IoStatus);
      
      IoFreeMdl(lMdl);
      
      if(!NT_SUCCESS(IoStatus.Status)){
         // Error
         return STATUS_UNSUCCESSFUL;
      }
      
      if(SizeToDump != Ttail-Thead){
         // Size limit reached.
         Open->DumpLimitReached = TRUE;

         // Awake the application
         KeSetEvent(Open->ReadEvent,0,FALSE);
         
         return STATUS_UNSUCCESSFUL;
      }
      
      // Update the packet buffer
      Open->DumpOffset.QuadPart+=(Ttail-Thead);         
      Open->Bhead=Ttail;
      
   }
#endif
   return STATUS_SUCCESS;
}