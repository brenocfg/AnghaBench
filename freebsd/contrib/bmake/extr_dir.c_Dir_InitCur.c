#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int refCount; } ;
typedef  TYPE_1__ Path ;

/* Variables and functions */
 TYPE_1__* Dir_AddDir (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  Dir_Destroy (TYPE_1__*) ; 
 TYPE_1__* cur ; 

void
Dir_InitCur(const char *cdname)
{
    Path *p;
    
    if (cdname != NULL) {
	/*
	 * Our build directory is not the same as our source directory.
	 * Keep this one around too.
	 */
	if ((p = Dir_AddDir(NULL, cdname))) {
	    p->refCount += 1;
	    if (cur && cur != p) {
		/*
		 * We've been here before, cleanup.
		 */
		cur->refCount -= 1;
		Dir_Destroy(cur);
	    }
	    cur = p;
	}
    }
}