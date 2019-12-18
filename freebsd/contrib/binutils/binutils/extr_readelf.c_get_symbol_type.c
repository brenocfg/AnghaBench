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
 int /*<<< orphan*/  EM_ARM ; 
 int /*<<< orphan*/  EM_PARISC ; 
 int /*<<< orphan*/  EM_SPARCV9 ; 
 unsigned int STT_ARM_TFUNC ; 
#define  STT_COMMON 136 
#define  STT_FILE 135 
#define  STT_FUNC 134 
 unsigned int STT_HIOS ; 
 unsigned int STT_HIPROC ; 
 unsigned int STT_HP_OPAQUE ; 
 unsigned int STT_HP_STUB ; 
 unsigned int STT_LOOS ; 
 unsigned int STT_LOPROC ; 
#define  STT_NOTYPE 133 
#define  STT_OBJECT 132 
 unsigned int STT_PARISC_MILLI ; 
 unsigned int STT_REGISTER ; 
#define  STT_RELC 131 
#define  STT_SECTION 130 
#define  STT_SRELC 129 
#define  STT_TLS 128 
 char* _ (char*) ; 
 TYPE_1__ elf_header ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
get_symbol_type (unsigned int type)
{
  static char buff[32];

  switch (type)
    {
    case STT_NOTYPE:	return "NOTYPE";
    case STT_OBJECT:	return "OBJECT";
    case STT_FUNC:	return "FUNC";
    case STT_SECTION:	return "SECTION";
    case STT_FILE:	return "FILE";
    case STT_COMMON:	return "COMMON";
    case STT_TLS:	return "TLS";
    case STT_RELC:      return "RELC";
    case STT_SRELC:     return "SRELC";
    default:
      if (type >= STT_LOPROC && type <= STT_HIPROC)
	{
	  if (elf_header.e_machine == EM_ARM && type == STT_ARM_TFUNC)
	    return "THUMB_FUNC";

	  if (elf_header.e_machine == EM_SPARCV9 && type == STT_REGISTER)
	    return "REGISTER";

	  if (elf_header.e_machine == EM_PARISC && type == STT_PARISC_MILLI)
	    return "PARISC_MILLI";

	  snprintf (buff, sizeof (buff), _("<processor specific>: %d"), type);
	}
      else if (type >= STT_LOOS && type <= STT_HIOS)
	{
	  if (elf_header.e_machine == EM_PARISC)
	    {
	      if (type == STT_HP_OPAQUE)
		return "HP_OPAQUE";
	      if (type == STT_HP_STUB)
		return "HP_STUB";
	    }

	  snprintf (buff, sizeof (buff), _("<OS specific>: %d"), type);
	}
      else
	snprintf (buff, sizeof (buff), _("<unknown>: %d"), type);
      return buff;
    }
}