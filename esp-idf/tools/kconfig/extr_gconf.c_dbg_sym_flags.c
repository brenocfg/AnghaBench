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
 int SYMBOL_AUTO ; 
 int SYMBOL_CHANGED ; 
 int SYMBOL_CHECK ; 
 int SYMBOL_CHOICE ; 
 int SYMBOL_CHOICEVAL ; 
 int SYMBOL_CONST ; 
 int SYMBOL_OPTIONAL ; 
 int SYMBOL_VALID ; 
 int SYMBOL_WRITE ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 

const char *dbg_sym_flags(int val)
{
	static char buf[256];

	bzero(buf, 256);

	if (val & SYMBOL_CONST)
		strcat(buf, "const/");
	if (val & SYMBOL_CHECK)
		strcat(buf, "check/");
	if (val & SYMBOL_CHOICE)
		strcat(buf, "choice/");
	if (val & SYMBOL_CHOICEVAL)
		strcat(buf, "choiceval/");
	if (val & SYMBOL_VALID)
		strcat(buf, "valid/");
	if (val & SYMBOL_OPTIONAL)
		strcat(buf, "optional/");
	if (val & SYMBOL_WRITE)
		strcat(buf, "write/");
	if (val & SYMBOL_CHANGED)
		strcat(buf, "changed/");
	if (val & SYMBOL_AUTO)
		strcat(buf, "auto/");

	buf[strlen(buf) - 1] = '\0';

	return buf;
}