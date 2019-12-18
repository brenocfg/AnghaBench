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
struct bsdar {int options; } ;

/* Variables and functions */
 int AR_BSD ; 
 int /*<<< orphan*/  AR_STRINGTAB_NAME_SVR4 ; 
 int /*<<< orphan*/  AR_SYMTAB_NAME_BSD ; 
 int /*<<< orphan*/  AR_SYMTAB_NAME_SVR4 ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int
bsdar_is_pseudomember(struct bsdar *bsdar, const char *name)
{
	/*
	 * The "__.SYMDEF" member is special in the BSD format
	 * variant.
	 */
	if (bsdar->options & AR_BSD)
		return (strcmp(name, AR_SYMTAB_NAME_BSD) == 0);
	else
		/*
		 * The names "/ " and "// " are special in the SVR4
		 * variant.
		 */
		return (strcmp(name, AR_STRINGTAB_NAME_SVR4) == 0 ||
		    strcmp(name, AR_SYMTAB_NAME_SVR4) == 0);
}