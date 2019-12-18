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
struct TYPE_4__ {int type; char* path; char* name; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,char*) ; 
 int OP_JOIN ; 
 int OP_PHONY ; 
 int /*<<< orphan*/  Targ_Precious (TYPE_1__*) ; 
 int eunlink (char*) ; 
 int /*<<< orphan*/  noExecute ; 

__attribute__((used)) static void
JobDeleteTarget(GNode *gn)
{
	if ((gn->type & (OP_JOIN|OP_PHONY)) == 0 && !Targ_Precious(gn)) {
	    char *file = (gn->path == NULL ? gn->name : gn->path);
	    if (!noExecute && eunlink(file) != -1) {
		Error("*** %s removed", file);
	    }
	}
}