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
struct TYPE_2__ {int e_machine; } ;

/* Variables and functions */
#define  EM_MIPS 128 
 char* _ (char*) ; 
 TYPE_1__ elf_header ; 
 char* get_mips_symbol_other (unsigned int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
get_symbol_other (unsigned int other)
{
  const char * result = NULL;
  static char buff [32];

  if (other == 0)
    return "";

  switch (elf_header.e_machine)
    {
    case EM_MIPS:
      result = get_mips_symbol_other (other);
    default:
      break;
    }

  if (result)
    return result;

  snprintf (buff, sizeof buff, _("<other>: %x"), other);
  return buff;
}