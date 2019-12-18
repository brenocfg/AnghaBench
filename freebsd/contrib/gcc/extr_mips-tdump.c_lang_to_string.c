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
typedef  int lang_t ;

/* Variables and functions */
#define  langAda 136 
#define  langAssembler 135 
#define  langC 134 
#define  langCobol 133 
#define  langFortran 132 
#define  langMachine 131 
#define  langNil 130 
#define  langPascal 129 
#define  langPl1 128 

__attribute__((used)) static const char *
lang_to_string (lang_t lang)
{
  switch (lang)
    {
    case langC:		return "C";
    case langPascal:	return "Pascal";
    case langFortran:	return "Fortran";
    case langAssembler:	return "Assembler";
    case langMachine:	return "Machine";
    case langNil:	return "Nil";
    case langAda:	return "Ada";
    case langPl1:	return "Pl1";
    case langCobol:	return "Cobol";
    }

  return "Unknown language";
}