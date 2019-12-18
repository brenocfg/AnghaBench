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
#define  NT_FREEBSD_ABI_TAG 141 
#define  NT_FREEBSD_ARCH_TAG 140 
#define  NT_FREEBSD_NOINIT_TAG 139 
#define  NT_PROCSTAT_AUXV 138 
#define  NT_PROCSTAT_FILES 137 
#define  NT_PROCSTAT_GROUPS 136 
#define  NT_PROCSTAT_OSREL 135 
#define  NT_PROCSTAT_PROC 134 
#define  NT_PROCSTAT_PSSTRINGS 133 
#define  NT_PROCSTAT_RLIMIT 132 
#define  NT_PROCSTAT_UMASK 131 
#define  NT_PROCSTAT_VMMAP 130 
#define  NT_THRMISC 129 
#define  NT_X86_XSTATE 128 
 char* _ (char*) ; 
 TYPE_1__ elf_header ; 
 char const* get_note_type (unsigned int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
get_freebsd_note_type (unsigned e_type)
{
  static char buff[64];

  if (elf_header.e_type == ET_CORE)
    switch (e_type)
      {
      case NT_THRMISC:
	return _("NT_THRMISC (thrmisc structure)");
      case NT_PROCSTAT_PROC:
	return _("NT_PROCSTAT_PROC (proc data)");
      case NT_PROCSTAT_FILES:
	return _("NT_PROCSTAT_FILES (files data)");
      case NT_PROCSTAT_VMMAP:
	return _("NT_PROCSTAT_VMMAP (vmmap data)");
      case NT_PROCSTAT_GROUPS:
	return _("NT_PROCSTAT_GROUPS (groups data)");
      case NT_PROCSTAT_UMASK:
	return _("NT_PROCSTAT_UMASK (umask data)");
      case NT_PROCSTAT_RLIMIT:
	return _("NT_PROCSTAT_RLIMIT (rlimit data)");
      case NT_PROCSTAT_OSREL:
	return _("NT_PROCSTAT_OSREL (osreldate data)");
      case NT_PROCSTAT_PSSTRINGS:
	return _("NT_PROCSTAT_PSSTRINGS (ps_strings data)");
      case NT_PROCSTAT_AUXV:
	return _("NT_PROCSTAT_AUXV (auxv data)");
      case NT_X86_XSTATE:
	return _("NT_X86_XSTATE (x86 XSAVE extended state)");
      default:
	return get_note_type(e_type);
      }
  else
    switch (e_type)
      {
      case NT_FREEBSD_ABI_TAG:
	return _("NT_FREEBSD_ABI_TAG");
      case NT_FREEBSD_NOINIT_TAG:
	return _("NT_FREEBSD_NOINIT_TAG");
      case NT_FREEBSD_ARCH_TAG:
	return _("NT_FREEBSD_ARCH_TAG");
      default:
	break;
      }

  snprintf (buff, sizeof(buff), _("Unknown note type: (0x%08x)"), e_type);
  return buff;
}