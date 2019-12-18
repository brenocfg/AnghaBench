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
typedef  int /*<<< orphan*/  tmp ;
typedef  int Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  VARF_WANTRES ; 
 int /*<<< orphan*/  VAR_CMD ; 
 char* Var_Subst (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

void
Main_ExportMAKEFLAGS(Boolean first)
{
    static int once = 1;
    char tmp[64];
    char *s;

    if (once != first)
	return;
    once = 0;
    
    strncpy(tmp, "${.MAKEFLAGS} ${.MAKEOVERRIDES:O:u:@v@$v=${$v:Q}@}",
	    sizeof(tmp));
    s = Var_Subst(NULL, tmp, VAR_CMD, VARF_WANTRES);
    if (s && *s) {
#ifdef POSIX
	setenv("MAKEFLAGS", s, 1);
#else
	setenv("MAKE", s, 1);
#endif
    }
}