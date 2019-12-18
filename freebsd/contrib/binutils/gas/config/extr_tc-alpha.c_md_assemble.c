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
typedef  int /*<<< orphan*/  opname ;
typedef  int /*<<< orphan*/  expressionS ;

/* Variables and functions */
 int MAX_INSN_ARGS ; 
 int TOKENIZE_ERROR_REPORT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  alpha_macros_on ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assemble_tokens (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 size_t strspn (char*,char*) ; 
 int tokenize_arguments (char*,int /*<<< orphan*/ *,int) ; 

void
md_assemble (char *str)
{
  /* Current maximum is 13.  */
  char opname[32];
  expressionS tok[MAX_INSN_ARGS];
  int ntok, trunclen;
  size_t opnamelen;

  /* Split off the opcode.  */
  opnamelen = strspn (str, "abcdefghijklmnopqrstuvwxyz_/46819");
  trunclen = (opnamelen < sizeof (opname) - 1
	      ? opnamelen
	      : sizeof (opname) - 1);
  memcpy (opname, str, trunclen);
  opname[trunclen] = '\0';

  /* Tokenize the rest of the line.  */
  if ((ntok = tokenize_arguments (str + opnamelen, tok, MAX_INSN_ARGS)) < 0)
    {
      if (ntok != TOKENIZE_ERROR_REPORT)
	as_bad (_("syntax error"));

      return;
    }

  /* Finish it off.  */
  assemble_tokens (opname, tok, ntok, alpha_macros_on);
}