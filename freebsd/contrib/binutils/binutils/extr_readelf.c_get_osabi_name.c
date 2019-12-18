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
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
#define  ELFOSABI_AIX 144 
#define  ELFOSABI_ARM 143 
#define  ELFOSABI_AROS 142 
#define  ELFOSABI_FREEBSD 141 
#define  ELFOSABI_HPUX 140 
#define  ELFOSABI_HURD 139 
#define  ELFOSABI_IRIX 138 
#define  ELFOSABI_LINUX 137 
#define  ELFOSABI_MODESTO 136 
#define  ELFOSABI_NETBSD 135 
#define  ELFOSABI_NONE 134 
#define  ELFOSABI_NSK 133 
#define  ELFOSABI_OPENBSD 132 
#define  ELFOSABI_OPENVMS 131 
#define  ELFOSABI_SOLARIS 130 
#define  ELFOSABI_STANDALONE 129 
#define  ELFOSABI_TRU64 128 
 char* _ (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
get_osabi_name (unsigned int osabi)
{
  static char buff[32];

  switch (osabi)
    {
    case ELFOSABI_NONE:		return "UNIX - System V";
    case ELFOSABI_HPUX:		return "UNIX - HP-UX";
    case ELFOSABI_NETBSD:	return "UNIX - NetBSD";
    case ELFOSABI_LINUX:	return "UNIX - Linux";
    case ELFOSABI_HURD:		return "GNU/Hurd";
    case ELFOSABI_SOLARIS:	return "UNIX - Solaris";
    case ELFOSABI_AIX:		return "UNIX - AIX";
    case ELFOSABI_IRIX:		return "UNIX - IRIX";
    case ELFOSABI_FREEBSD:	return "UNIX - FreeBSD";
    case ELFOSABI_TRU64:	return "UNIX - TRU64";
    case ELFOSABI_MODESTO:	return "Novell - Modesto";
    case ELFOSABI_OPENBSD:	return "UNIX - OpenBSD";
    case ELFOSABI_OPENVMS:	return "VMS - OpenVMS";
    case ELFOSABI_NSK:		return "HP - Non-Stop Kernel";
    case ELFOSABI_AROS:		return "Amiga Research OS";
    case ELFOSABI_STANDALONE:	return _("Standalone App");
    case ELFOSABI_ARM:		return "ARM";
    default:
      snprintf (buff, sizeof (buff), _("<unknown: %x>"), osabi);
      return buff;
    }
}