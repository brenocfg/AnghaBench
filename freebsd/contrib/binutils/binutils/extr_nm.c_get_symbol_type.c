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

/* Variables and functions */
#define  STT_COMMON 134 
#define  STT_FILE 133 
#define  STT_FUNC 132 
 unsigned int STT_HIOS ; 
 unsigned int STT_HIPROC ; 
 unsigned int STT_LOOS ; 
 unsigned int STT_LOPROC ; 
#define  STT_NOTYPE 131 
#define  STT_OBJECT 130 
#define  STT_SECTION 129 
#define  STT_TLS 128 
 char* _ (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static const char *
get_symbol_type (unsigned int type)
{
  static char buff [32];

  switch (type)
    {
    case STT_NOTYPE:   return "NOTYPE";
    case STT_OBJECT:   return "OBJECT";
    case STT_FUNC:     return "FUNC";
    case STT_SECTION:  return "SECTION";
    case STT_FILE:     return "FILE";
    case STT_COMMON:   return "COMMON";
    case STT_TLS:      return "TLS";
    default:
      if (type >= STT_LOPROC && type <= STT_HIPROC)
	sprintf (buff, _("<processor specific>: %d"), type);
      else if (type >= STT_LOOS && type <= STT_HIOS)
	sprintf (buff, _("<OS specific>: %d"), type);
      else
	sprintf (buff, _("<unknown>: %d"), type);
      return buff;
    }
}