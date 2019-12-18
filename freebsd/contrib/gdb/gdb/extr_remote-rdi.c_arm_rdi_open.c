#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct local_bp_list_entry {struct local_bp_list_entry* next; } ;
struct TYPE_6__ {int bytesex; int fpe; int rditype; int heartbeat_on; int flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  reset; int /*<<< orphan*/ * hostosarg; int /*<<< orphan*/  gets; int /*<<< orphan*/  write; int /*<<< orphan*/  readc; int /*<<< orphan*/  writec; int /*<<< orphan*/ * dbgarg; int /*<<< orphan*/  dbgpause; int /*<<< orphan*/  dbgprint; } ;

/* Variables and functions */
 int /*<<< orphan*/  Adp_CloseDevice () ; 
 int Adp_OpenDevice (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ BFD_ENDIAN_BIG ; 
 int RDIError_BigEndian ; 
 int RDIError_LittleEndian ; 
 int RDIError_NoError ; 
 int /*<<< orphan*/  RDIInfo_CoPro ; 
 int /*<<< orphan*/  RDIInfo_GetLoadSize ; 
 int /*<<< orphan*/  RDIInfo_Points ; 
 int /*<<< orphan*/  RDIInfo_SemiHosting ; 
 int /*<<< orphan*/  RDIInfo_Step ; 
 int /*<<< orphan*/  RDIInfo_Target ; 
 int /*<<< orphan*/  RDISet_Cmdline ; 
 int /*<<< orphan*/  RDIVector_Catch ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 int adp_ok ; 
 int angel_RDI_info (int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 
 int angel_RDI_open (int,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arm_rdi_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_rdi_ops ; 
 scalar_t__ closed_already ; 
 int /*<<< orphan*/  error (char*,...) ; 
 TYPE_2__ gdb_config ; 
 TYPE_1__ gdb_hostif ; 
 int /*<<< orphan*/  inferior_ptid ; 
 struct local_bp_list_entry* local_bp_list ; 
 unsigned long max_load_size ; 
 int /*<<< orphan*/  mygets ; 
 int /*<<< orphan*/  mypause ; 
 int /*<<< orphan*/  myprint ; 
 int /*<<< orphan*/  myreadc ; 
 int /*<<< orphan*/  mywrite ; 
 int /*<<< orphan*/  mywritec ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdi_error_message (int) ; 
 int /*<<< orphan*/  rdi_heartbeat ; 
 scalar_t__ rom_at_zero ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  target_fetch_registers (int) ; 
 int /*<<< orphan*/  voiddummy ; 
 int /*<<< orphan*/  xfree (struct local_bp_list_entry*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
arm_rdi_open (char *name, int from_tty)
{
  int rslt, i;
  unsigned long arg1, arg2;
  char *openArgs = NULL;
  char *devName = NULL;
  char *p;

  if (name == NULL)
    error ("To open an RDI connection, you need to specify what serial\n\
device is attached to the remote system (e.g. /dev/ttya).");

  /* split name after whitespace, pass tail as arg to open command */

  devName = xstrdup (name);
  p = strchr (devName, ' ');
  if (p)
    {
      *p = '\0';
      ++p;

      while (*p == ' ')
	++p;

      openArgs = p;
    }

  /* Make the basic low-level connection.  */

  arm_rdi_close (0);
  rslt = Adp_OpenDevice (devName, openArgs, rdi_heartbeat);

  if (rslt != adp_ok)
    error ("Could not open device \"%s\"", name);

  gdb_config.bytesex = 2 | (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG ? 1 : 0);
  gdb_config.fpe = 1;
  gdb_config.rditype = 2;
  gdb_config.heartbeat_on = 1;
  gdb_config.flags = 2;

  gdb_hostif.dbgprint = myprint;
  gdb_hostif.dbgpause = mypause;
  gdb_hostif.dbgarg = NULL;
  gdb_hostif.writec = mywritec;
  gdb_hostif.readc = myreadc;
  gdb_hostif.write = mywrite;
  gdb_hostif.gets = mygets;
  gdb_hostif.hostosarg = NULL;
  gdb_hostif.reset = voiddummy;

  rslt = angel_RDI_open (10, &gdb_config, &gdb_hostif, NULL);
  if (rslt == RDIError_BigEndian || rslt == RDIError_LittleEndian)
    ;				/* do nothing, this is the expected return */
  else if (rslt != RDIError_NoError)
    {
      printf_filtered ("RDI_open: %s\n", rdi_error_message (rslt));
      Adp_CloseDevice ();
      error ("RDI_open failed\n");
    }

  rslt = angel_RDI_info (RDIInfo_Target, &arg1, &arg2);
  if (rslt != RDIError_NoError)
    {
      printf_filtered ("RDI_info: %s\n", rdi_error_message (rslt));
    }
  rslt = angel_RDI_info (RDIInfo_Points, &arg1, &arg2);
  if (rslt != RDIError_NoError)
    {
      printf_filtered ("RDI_info: %s\n", rdi_error_message (rslt));
    }
  rslt = angel_RDI_info (RDIInfo_Step, &arg1, &arg2);
  if (rslt != RDIError_NoError)
    {
      printf_filtered ("RDI_info: %s\n", rdi_error_message (rslt));
    }
  rslt = angel_RDI_info (RDIInfo_CoPro, &arg1, &arg2);
  if (rslt != RDIError_NoError)
    {
      printf_filtered ("RDI_info: %s\n", rdi_error_message (rslt));
    }
  rslt = angel_RDI_info (RDIInfo_SemiHosting, &arg1, &arg2);
  if (rslt != RDIError_NoError)
    {
      printf_filtered ("RDI_info: %s\n", rdi_error_message (rslt));
    }

  rslt = angel_RDI_info (RDIInfo_GetLoadSize, &arg1, &arg2);
  if (rslt != RDIError_NoError)
    {
      printf_filtered ("RDI_info: %s\n", rdi_error_message (rslt));
    }
  max_load_size = arg1;

  push_target (&arm_rdi_ops);

  target_fetch_registers (-1);

  rslt = angel_RDI_open (1, &gdb_config, NULL, NULL);
  if (rslt != RDIError_NoError)
    {
      printf_filtered ("RDI_open: %s\n", rdi_error_message (rslt));
    }

  arg1 = rom_at_zero ? 0x0 : 0x13b;

  rslt = angel_RDI_info (RDIVector_Catch, &arg1, &arg2);
  if (rslt != RDIError_NoError)
    {
      printf_filtered ("RDI_info: %s\n", rdi_error_message (rslt));
    }

  arg1 = (unsigned long) "";
  rslt = angel_RDI_info (RDISet_Cmdline, &arg1, &arg2);
  if (rslt != RDIError_NoError)
    {
      printf_filtered ("RDI_info: %s\n", rdi_error_message (rslt));
    }

  /* Clear out any existing records of breakpoints.  */
  {
    struct local_bp_list_entry *entry, *preventry = NULL;

    for (entry = local_bp_list; entry != NULL; entry = entry->next)
      {
	if (preventry)
	  xfree (preventry);
      }
  }

  printf_filtered ("Connected to ARM RDI target.\n");
  closed_already = 0;
  inferior_ptid = pid_to_ptid (42);
}