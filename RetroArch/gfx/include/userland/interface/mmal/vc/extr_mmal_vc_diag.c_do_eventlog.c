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
typedef  int /*<<< orphan*/  log ;
typedef  int VC_MEM_ADDR_T ;
typedef  int /*<<< orphan*/  VC_MEM_ACCESS_HANDLE_T ;
struct TYPE_4__ {int magic; int size; int elemsize; int version; int index; int num_entries; } ;
typedef  TYPE_1__ MMAL_DBG_LOG_T ;
typedef  int /*<<< orphan*/  MMAL_DBG_ENTRY_T ;

/* Variables and functions */
 int /*<<< orphan*/  CloseVideoCoreMemory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LookupVideoCoreSymbol (int /*<<< orphan*/ ,char*,int*,size_t*) ; 
 int MMAL_MAGIC ; 
 int OpenVideoCoreMemory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReadVideoCoreMemory (int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ReadVideoCoreUInt32 (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_mmal_event_log (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int do_eventlog(int argc, const char **argv)
{
   VC_MEM_ACCESS_HANDLE_T vc;
   VC_MEM_ADDR_T addr;     /** The address of the pointer to the log */
   size_t size;
   VC_MEM_ADDR_T logaddr;       /** The address of the log itself */
   MMAL_DBG_LOG_T log;

   (void)argc; (void)argv;
   int rc;
   if ((rc = OpenVideoCoreMemory(&vc)) < 0)
   {
      fprintf(stderr,"Unable to open videocore memory: %d\n", rc);
      return -1;
   }
   if (!LookupVideoCoreSymbol(vc, "mmal_dbg_log", &addr, &size))
   {
      fprintf(stderr,"Could not get MMAL log address\n");
      goto fail;
   }
   if (!ReadVideoCoreUInt32(vc, &logaddr, addr))
   {
      fprintf(stderr,"Could not read MMAL log pointer at address 0x%x\n",
              addr);
      goto fail;
   }
   if (!ReadVideoCoreMemory(vc, &log, logaddr, sizeof(log)))
   {
      fprintf(stderr,"Could not read MMAL log at address 0x%x\n",
              logaddr);
      goto fail;
   }
   if (log.magic != MMAL_MAGIC)
   {
      fprintf(stderr,"Bad magic 0x%08x in log at 0x%x\n", log.magic, logaddr);
      goto fail;
   }
   if (log.size != sizeof(log))
   {
      fprintf(stderr,"MMAL Log size mismatch (got %d, expected %d)\n",
              log.size, sizeof(log));
      goto fail;
   }
   if (log.elemsize != sizeof(MMAL_DBG_ENTRY_T))
   {
      fprintf(stderr,"MMAL log element size mismatch (got %d, expected %d)\n",
              log.elemsize, sizeof(MMAL_DBG_ENTRY_T));
      goto fail;
   }

   printf("reading MMAL log at 0x%x version %d magic %x\n",
          logaddr, log.version, log.magic);
   printf("%d events, %d entries each size %d\n", log.index, log.num_entries,
          log.elemsize);
   print_mmal_event_log(vc, &log);

   CloseVideoCoreMemory(vc);
   return 0;
fail:
   CloseVideoCoreMemory(vc);
   return -1;

}