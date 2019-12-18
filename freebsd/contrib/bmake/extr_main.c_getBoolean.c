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
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  VARF_WANTRES ; 
 int /*<<< orphan*/  VAR_GLOBAL ; 
 char* Var_Subst (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  s2Boolean (char*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char const*) ; 

Boolean
getBoolean(const char *name, Boolean bf)
{
    char tmp[64];
    char *cp;

    if (snprintf(tmp, sizeof(tmp), "${%s:U:tl}", name) < (int)(sizeof(tmp))) {
	cp = Var_Subst(NULL, tmp, VAR_GLOBAL, VARF_WANTRES);

	if (cp) {
	    bf = s2Boolean(cp, bf);
	    free(cp);
	}
    }
    return (bf);
}