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
 int /*<<< orphan*/  error (char*,char*,char*,char*,int,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
undef_cmd_error (char *cmdtype, char *q)
{
  error ("Undefined %scommand: \"%s\".  Try \"help%s%.*s\".",
	 cmdtype,
	 q,
	 *cmdtype ? " " : "",
	 (int) strlen (cmdtype) - 1,
	 cmdtype);
}