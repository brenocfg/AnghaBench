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