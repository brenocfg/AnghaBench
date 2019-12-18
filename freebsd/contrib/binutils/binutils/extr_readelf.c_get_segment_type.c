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
struct TYPE_2__ {int /*<<< orphan*/  e_machine; } ;

/* Variables and functions */
#define  EM_ARM 143 
#define  EM_IA_64 142 
#define  EM_MIPS 141 
#define  EM_MIPS_RS3_LE 140 
#define  EM_PARISC 139 
#define  PT_DYNAMIC 138 
#define  PT_GNU_EH_FRAME 137 
#define  PT_GNU_RELRO 136 
#define  PT_GNU_STACK 135 
 unsigned long PT_HIOS ; 
 unsigned long PT_HIPROC ; 
#define  PT_INTERP 134 
#define  PT_LOAD 133 
 unsigned long PT_LOOS ; 
 unsigned long PT_LOPROC ; 
#define  PT_NOTE 132 
#define  PT_NULL 131 
#define  PT_PHDR 130 
#define  PT_SHLIB 129 
#define  PT_TLS 128 
 char* _ (char*) ; 
 TYPE_1__ elf_header ; 
 char* get_arm_segment_type (unsigned long) ; 
 char* get_ia64_segment_type (unsigned long) ; 
 char* get_mips_segment_type (unsigned long) ; 
 char* get_parisc_segment_type (unsigned long) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
get_segment_type (unsigned long p_type)
{
  static char buff[32];

  switch (p_type)
    {
    case PT_NULL:	return "NULL";
    case PT_LOAD:	return "LOAD";
    case PT_DYNAMIC:	return "DYNAMIC";
    case PT_INTERP:	return "INTERP";
    case PT_NOTE:	return "NOTE";
    case PT_SHLIB:	return "SHLIB";
    case PT_PHDR:	return "PHDR";
    case PT_TLS:	return "TLS";

    case PT_GNU_EH_FRAME:
			return "GNU_EH_FRAME";
    case PT_GNU_STACK:	return "GNU_STACK";
    case PT_GNU_RELRO:  return "GNU_RELRO";

    default:
      if ((p_type >= PT_LOPROC) && (p_type <= PT_HIPROC))
	{
	  const char *result;

	  switch (elf_header.e_machine)
	    {
	    case EM_ARM:
	      result = get_arm_segment_type (p_type);
	      break;
	    case EM_MIPS:
	    case EM_MIPS_RS3_LE:
	      result = get_mips_segment_type (p_type);
	      break;
	    case EM_PARISC:
	      result = get_parisc_segment_type (p_type);
	      break;
	    case EM_IA_64:
	      result = get_ia64_segment_type (p_type);
	      break;
	    default:
	      result = NULL;
	      break;
	    }

	  if (result != NULL)
	    return result;

	  sprintf (buff, "LOPROC+%lx", p_type - PT_LOPROC);
	}
      else if ((p_type >= PT_LOOS) && (p_type <= PT_HIOS))
	{
	  const char *result;

	  switch (elf_header.e_machine)
	    {
	    case EM_PARISC:
	      result = get_parisc_segment_type (p_type);
	      break;
	    case EM_IA_64:
	      result = get_ia64_segment_type (p_type);
	      break;
	    default:
	      result = NULL;
	      break;
	    }

	  if (result != NULL)
	    return result;

	  sprintf (buff, "LOOS+%lx", p_type - PT_LOOS);
	}
      else
	snprintf (buff, sizeof (buff), _("<unknown>: %lx"), p_type);

      return buff;
    }
}