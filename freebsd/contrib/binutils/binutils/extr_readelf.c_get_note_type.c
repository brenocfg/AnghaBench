#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buff ;
struct TYPE_2__ {scalar_t__ e_type; } ;

/* Variables and functions */
 scalar_t__ ET_CORE ; 
#define  NT_ARCH 143 
#define  NT_AUXV 142 
#define  NT_FILE 141 
#define  NT_FPREGS 140 
#define  NT_FPREGSET 139 
#define  NT_LWPSINFO 138 
#define  NT_LWPSTATUS 137 
#define  NT_PRPSINFO 136 
#define  NT_PRSTATUS 135 
#define  NT_PRXFPREG 134 
#define  NT_PSINFO 133 
#define  NT_PSTATUS 132 
#define  NT_SIGINFO 131 
#define  NT_TASKSTRUCT 130 
#define  NT_VERSION 129 
#define  NT_WIN32PSTATUS 128 
 char* _ (char*) ; 
 TYPE_1__ elf_header ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
get_note_type (unsigned e_type)
{
  static char buff[64];

  if (elf_header.e_type == ET_CORE)
    switch (e_type)
      {
      case NT_AUXV:
	return _("NT_AUXV (auxiliary vector)");
      case NT_PRSTATUS:
	return _("NT_PRSTATUS (prstatus structure)");
      case NT_FPREGSET:
	return _("NT_FPREGSET (floating point registers)");
      case NT_PRPSINFO:
	return _("NT_PRPSINFO (prpsinfo structure)");
      case NT_TASKSTRUCT:
	return _("NT_TASKSTRUCT (task structure)");
      case NT_PRXFPREG:
	return _("NT_PRXFPREG (user_xfpregs structure)");
      case NT_PSTATUS:
	return _("NT_PSTATUS (pstatus structure)");
      case NT_FPREGS:
	return _("NT_FPREGS (floating point registers)");
      case NT_PSINFO:
	return _("NT_PSINFO (psinfo structure)");
      case NT_LWPSTATUS:
	return _("NT_LWPSTATUS (lwpstatus_t structure)");
      case NT_LWPSINFO:
	return _("NT_LWPSINFO (lwpsinfo_t structure)");
      case NT_WIN32PSTATUS:
	return _("NT_WIN32PSTATUS (win32_pstatus structure)");
      case NT_FILE:
        return _("NT_FILE");
      case NT_SIGINFO:
        return _("NT_SIGINFO");
      default:
	break;
      }
  else
    switch (e_type)
      {
      case NT_VERSION:
	return _("NT_VERSION (version)");
      case NT_ARCH:
	return _("NT_ARCH (architecture)");
      default:
	break;
      }

  snprintf (buff, sizeof (buff), _("Unknown note type: (0x%08x)"), e_type);
  return buff;
}