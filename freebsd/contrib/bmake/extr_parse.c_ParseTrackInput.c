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
 int /*<<< orphan*/  MAKE_MAKEFILES ; 
 int /*<<< orphan*/  VAR_GLOBAL ; 
 int /*<<< orphan*/  Var_Append (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 char* Var_Value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ memcmp (char*,char const*,size_t) ; 
 char* strchr (char*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
ParseTrackInput(const char *name)
{
    char *old;
    char *ep;
    char *fp = NULL;
    size_t name_len = strlen(name);
    
    old = Var_Value(MAKE_MAKEFILES, VAR_GLOBAL, &fp);
    if (old) {
	ep = old + strlen(old) - name_len;
	/* does it contain name? */
	for (; old != NULL; old = strchr(old, ' ')) {
	    if (*old == ' ')
		old++;
	    if (old >= ep)
		break;			/* cannot contain name */
	    if (memcmp(old, name, name_len) == 0
		    && (old[name_len] == 0 || old[name_len] == ' '))
		goto cleanup;
	}
    }
    Var_Append (MAKE_MAKEFILES, name, VAR_GLOBAL);
 cleanup:
    if (fp) {
	free(fp);
    }
}