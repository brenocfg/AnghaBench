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
struct TYPE_4__ {char* name; char* path; } ;
typedef  int /*<<< orphan*/  Lst ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 char* Dir_FindFile (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET ; 
 int /*<<< orphan*/  Var_Set (int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* bmake_malloc (size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 int strlen (char*) ; 

void
Arch_FindLib(GNode *gn, Lst path)
{
    char	    *libName;   /* file name for archive */
    size_t	     sz = strlen(gn->name) + 6 - 2;

    libName = bmake_malloc(sz);
    snprintf(libName, sz, "lib%s.a", &gn->name[2]);

    gn->path = Dir_FindFile(libName, path);

    free(libName);

#ifdef LIBRARIES
    Var_Set(TARGET, gn->name, gn, 0);
#else
    Var_Set(TARGET, gn->path == NULL ? gn->name : gn->path, gn, 0);
#endif /* LIBRARIES */
}