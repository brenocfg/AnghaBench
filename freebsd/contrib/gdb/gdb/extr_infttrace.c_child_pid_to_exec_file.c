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
typedef  int /*<<< orphan*/  uint64_t ;
struct pst_status {char* pst_cmd; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  exec_file_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  TT_PROC_GET_PATHNAME ; 
 int call_ttrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pstat_getproc (struct pst_status*,int,int /*<<< orphan*/ ,int) ; 

char *
child_pid_to_exec_file (int tid)
{
  int tt_status;
  static char exec_file_buffer[1024];
  pid_t pid;
  static struct pst_status buf;

  /* On various versions of hpux11, this may fail due to a supposed
     kernel bug.  We have alternate methods to get this information
     (ie pstat).  */
  tt_status = call_ttrace (TT_PROC_GET_PATHNAME,
			   tid,
			   (uint64_t) exec_file_buffer,
			   sizeof (exec_file_buffer) - 1,
			   0);
  if (tt_status >= 0)
    return exec_file_buffer;

  /* Try to get process information via pstat and extract the filename
     from the pst_cmd field within the pst_status structure.  */
  if (pstat_getproc (&buf, sizeof (struct pst_status), 0, tid) != -1)
    {
      char *p = buf.pst_cmd;

      while (*p && *p != ' ')
	p++;
      *p = 0;

      return (buf.pst_cmd);
    }

  return (NULL);
}