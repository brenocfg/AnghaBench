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
#define  STB_GLOBAL 130 
 unsigned int STB_HIOS ; 
 unsigned int STB_HIPROC ; 
#define  STB_LOCAL 129 
 unsigned int STB_LOOS ; 
 unsigned int STB_LOPROC ; 
#define  STB_WEAK 128 
 char* _ (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
get_symbol_binding (unsigned int binding)
{
  static char buff[32];

  switch (binding)
    {
    case STB_LOCAL:	return "LOCAL";
    case STB_GLOBAL:	return "GLOBAL";
    case STB_WEAK:	return "WEAK";
    default:
      if (binding >= STB_LOPROC && binding <= STB_HIPROC)
	snprintf (buff, sizeof (buff), _("<processor specific>: %d"),
		  binding);
      else if (binding >= STB_LOOS && binding <= STB_HIOS)
	snprintf (buff, sizeof (buff), _("<OS specific>: %d"), binding);
      else
	snprintf (buff, sizeof (buff), _("<unknown>: %d"), binding);
      return buff;
    }
}