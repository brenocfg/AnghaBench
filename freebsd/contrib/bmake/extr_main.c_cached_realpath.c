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
typedef  int /*<<< orphan*/  GNode ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  Var_Set (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* Var_Value (char const*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * get_cached_realpaths () ; 
 char* realpath (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 

char *
cached_realpath(const char *pathname, char *resolved)
{
    GNode *cache;
    char *rp, *cp;

    if (!pathname || !pathname[0])
	return NULL;

    cache = get_cached_realpaths();

    if ((rp = Var_Value(pathname, cache, &cp)) != NULL) {
	/* a hit */
	strlcpy(resolved, rp, MAXPATHLEN);
    } else if ((rp = realpath(pathname, resolved)) != NULL) {
	Var_Set(pathname, rp, cache, 0);
    }
    free(cp);
    return rp ? resolved : NULL;
}