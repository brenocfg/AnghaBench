#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Path ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIR ; 
 int /*<<< orphan*/  STR_ADDSLASH ; 
 char* bmake_strdup (char const*) ; 
 scalar_t__ cached_stat (char*,struct stat*) ; 
 int /*<<< orphan*/  debug_file ; 
 TYPE_1__* dot ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int nearmisses ; 
 char* str_concat (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
DirLookupSubdir(Path *p, const char *name)
{
    struct stat	  stb;		/* Buffer for stat, if necessary */
    char 	 *file;		/* the current filename to check */

    if (p != dot) {
	file = str_concat(p->name, name, STR_ADDSLASH);
    } else {
	/*
	 * Checking in dot -- DON'T put a leading ./ on the thing.
	 */
	file = bmake_strdup(name);
    }

    if (DEBUG(DIR)) {
	fprintf(debug_file, "checking %s ...\n", file);
    }

    if (cached_stat(file, &stb) == 0) {
	nearmisses += 1;
	return (file);
    }
    free(file);
    return NULL;
}