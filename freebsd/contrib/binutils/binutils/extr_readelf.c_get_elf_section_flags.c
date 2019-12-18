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
typedef  int bfd_vma ;
struct TYPE_2__ {int /*<<< orphan*/  e_machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  EM_X86_64 ; 
#define  SHF_ALLOC 137 
#define  SHF_EXECINSTR 136 
#define  SHF_GROUP 135 
#define  SHF_INFO_LINK 134 
#define  SHF_LINK_ORDER 133 
 int SHF_MASKOS ; 
 int SHF_MASKPROC ; 
#define  SHF_MERGE 132 
#define  SHF_OS_NONCONFORMING 131 
#define  SHF_STRINGS 130 
#define  SHF_TLS 129 
#define  SHF_WRITE 128 
 int SHF_X86_64_LARGE ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ do_section_details ; 
 TYPE_1__ elf_header ; 
 scalar_t__ is_32bit_elf ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,unsigned long) ; 
 char* stpcpy (char*,char const*) ; 

__attribute__((used)) static const char *
get_elf_section_flags (bfd_vma sh_flags)
{
  static char buff[1024];
  char *p = buff;
  int field_size = is_32bit_elf ? 8 : 16;
  int index, size = sizeof (buff) - (field_size + 4 + 1);
  bfd_vma os_flags = 0;
  bfd_vma proc_flags = 0;
  bfd_vma unknown_flags = 0;
  const struct
    {
      const char *str;
      int len;
    }
  flags [] =
    {
	{ "WRITE", 5 },
	{ "ALLOC", 5 },
	{ "EXEC", 4 },
	{ "MERGE", 5 },
	{ "STRINGS", 7 },
	{ "INFO LINK", 9 },
	{ "LINK ORDER", 10 },
	{ "OS NONCONF", 10 },
	{ "GROUP", 5 },
	{ "TLS", 3 }
    };

  if (do_section_details)
    {
      sprintf (buff, "[%*.*lx]: ",
	       field_size, field_size, (unsigned long) sh_flags);
      p += field_size + 4;
    }

  while (sh_flags)
    {
      bfd_vma flag;

      flag = sh_flags & - sh_flags;
      sh_flags &= ~ flag;

      if (do_section_details)
	{
	  switch (flag)
	    {
	    case SHF_WRITE:		index = 0; break;
	    case SHF_ALLOC:		index = 1; break;
	    case SHF_EXECINSTR:		index = 2; break;
	    case SHF_MERGE:		index = 3; break;
	    case SHF_STRINGS:		index = 4; break;
	    case SHF_INFO_LINK:		index = 5; break;
	    case SHF_LINK_ORDER:	index = 6; break;
	    case SHF_OS_NONCONFORMING:	index = 7; break;
	    case SHF_GROUP:		index = 8; break;
	    case SHF_TLS:		index = 9; break;

	    default:
	      index = -1;
	      break;
	    }

	  if (index != -1)
	    {
	      if (p != buff + field_size + 4)
		{
		  if (size < (10 + 2))
		    abort ();
		  size -= 2;
		  *p++ = ',';
		  *p++ = ' ';
		}

	      size -= flags [index].len;
	      p = stpcpy (p, flags [index].str);
	    }
	  else if (flag & SHF_MASKOS)
	    os_flags |= flag;
	  else if (flag & SHF_MASKPROC)
	    proc_flags |= flag;
	  else
	    unknown_flags |= flag;
	}
      else
	{
	  switch (flag)
	    {
	    case SHF_WRITE:		*p = 'W'; break;
	    case SHF_ALLOC:		*p = 'A'; break;
	    case SHF_EXECINSTR:		*p = 'X'; break;
	    case SHF_MERGE:		*p = 'M'; break;
	    case SHF_STRINGS:		*p = 'S'; break;
	    case SHF_INFO_LINK:		*p = 'I'; break;
	    case SHF_LINK_ORDER:	*p = 'L'; break;
	    case SHF_OS_NONCONFORMING:	*p = 'O'; break;
	    case SHF_GROUP:		*p = 'G'; break;
	    case SHF_TLS:		*p = 'T'; break;

	    default:
	      if (elf_header.e_machine == EM_X86_64
		  && flag == SHF_X86_64_LARGE)
		*p = 'l';
	      else if (flag & SHF_MASKOS)
		{
		  *p = 'o';
		  sh_flags &= ~ SHF_MASKOS;
		}
	      else if (flag & SHF_MASKPROC)
		{
		  *p = 'p';
		  sh_flags &= ~ SHF_MASKPROC;
		}
	      else
		*p = 'x';
	      break;
	    }
	  p++;
	}
    }

  if (do_section_details)
    {
      if (os_flags)
	{
	  size -= 5 + field_size;
	  if (p != buff + field_size + 4)
	    {
	      if (size < (2 + 1))
		abort ();
	      size -= 2;
	      *p++ = ',';
	      *p++ = ' ';
	    }
	  sprintf (p, "OS (%*.*lx)", field_size, field_size,
		   (unsigned long) os_flags);
	  p += 5 + field_size;
	}
      if (proc_flags)
	{
	  size -= 7 + field_size;
	  if (p != buff + field_size + 4)
	    {
	      if (size < (2 + 1))
		abort ();
	      size -= 2;
	      *p++ = ',';
	      *p++ = ' ';
	    }
	  sprintf (p, "PROC (%*.*lx)", field_size, field_size,
		   (unsigned long) proc_flags);
	  p += 7 + field_size;
	}
      if (unknown_flags)
	{
	  size -= 10 + field_size;
	  if (p != buff + field_size + 4)
	    {
	      if (size < (2 + 1))
		abort ();
	      size -= 2;
	      *p++ = ',';
	      *p++ = ' ';
	    }
	  sprintf (p, "UNKNOWN (%*.*lx)", field_size, field_size,
		   (unsigned long) unknown_flags);
	  p += 10 + field_size;
	}
    }

  *p = '\0';
  return buff;
}