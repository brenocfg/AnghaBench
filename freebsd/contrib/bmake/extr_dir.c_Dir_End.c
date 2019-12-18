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

/* Variables and functions */
 int /*<<< orphan*/  Dir_ClearPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Dir_Destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  Hash_DeleteTable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_Destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* cur ; 
 int /*<<< orphan*/  dirSearchPath ; 
 TYPE_1__* dot ; 
 TYPE_1__* dotLast ; 
 int /*<<< orphan*/  mtimes ; 
 int /*<<< orphan*/  openDirectories ; 

void
Dir_End(void)
{
#ifdef CLEANUP
    if (cur) {
	cur->refCount -= 1;
	Dir_Destroy(cur);
    }
    dot->refCount -= 1;
    dotLast->refCount -= 1;
    Dir_Destroy(dotLast);
    Dir_Destroy(dot);
    Dir_ClearPath(dirSearchPath);
    Lst_Destroy(dirSearchPath, NULL);
    Dir_ClearPath(openDirectories);
    Lst_Destroy(openDirectories, NULL);
    Hash_DeleteTable(&mtimes);
#endif
}