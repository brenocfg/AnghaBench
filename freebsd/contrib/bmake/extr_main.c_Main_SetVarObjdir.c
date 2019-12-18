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
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Main_SetObjdir (char*,char*,char const*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VARF_WANTRES ; 
 int /*<<< orphan*/  VAR_CMD ; 
 int /*<<< orphan*/  VAR_GLOBAL ; 
 char* Var_Subst (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* Var_Value (char const*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strchr (char*,char) ; 

__attribute__((used)) static Boolean
Main_SetVarObjdir(const char *var, const char *suffix)
{
	char *p, *path, *xpath;

	if ((path = Var_Value(var, VAR_CMD, &p)) == NULL ||
	    *path == '\0')
		return FALSE;

	/* expand variable substitutions */
	if (strchr(path, '$') != 0)
		xpath = Var_Subst(NULL, path, VAR_GLOBAL, VARF_WANTRES);
	else
		xpath = path;

	(void)Main_SetObjdir("%s%s", xpath, suffix);

	if (xpath != path)
		free(xpath);
	free(p);
	return TRUE;
}