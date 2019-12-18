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
struct spu_opcode {char* mnemonic; int* arg; } ;

/* Variables and functions */
 int A_P ; 
 scalar_t__ sprintf (char*,char*,char*) ; 
 int syntax_error_arg ; 

__attribute__((used)) static char *
insn_fmt_string (struct spu_opcode *format)
{
  static char buf[64];
  int len = 0;
  int i;

  len += sprintf (&buf[len], "%s\t", format->mnemonic);
  for (i = 1; i <= format->arg[0]; i++)
    {
      int arg = format->arg[i];
      char *exp;
      if (i > 1 && arg != A_P && format->arg[i-1] != A_P) 
	buf[len++] =  ',';
      if (arg == A_P)
	exp = "(";
      else if (arg < A_P)
	exp = i == syntax_error_arg ? "REG" : "reg";
      else 
	exp = i == syntax_error_arg ? "IMM" : "imm";
      len += sprintf (&buf[len], "%s", exp);
      if (i > 1 && format->arg[i-1] == A_P) 
	buf[len++] =  ')';
    }
  buf[len] = 0;
  return buf;
}