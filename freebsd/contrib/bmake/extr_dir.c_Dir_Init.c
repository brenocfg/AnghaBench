#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int refCount; int /*<<< orphan*/  files; int /*<<< orphan*/  name; scalar_t__ hits; } ;
typedef  int /*<<< orphan*/  Path ;

/* Variables and functions */
 int /*<<< orphan*/  Dir_InitCur (char const*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Hash_InitTable (int /*<<< orphan*/ *,int) ; 
 void* Lst_Init (int /*<<< orphan*/ ) ; 
 TYPE_1__* bmake_malloc (int) ; 
 int /*<<< orphan*/  bmake_strdup (char*) ; 
 void* dirSearchPath ; 
 TYPE_1__* dotLast ; 
 int /*<<< orphan*/  lmtimes ; 
 int /*<<< orphan*/  mtimes ; 
 void* openDirectories ; 

void
Dir_Init(const char *cdname)
{
    if (!cdname) {
	dirSearchPath = Lst_Init(FALSE);
	openDirectories = Lst_Init(FALSE);
	Hash_InitTable(&mtimes, 0);
	Hash_InitTable(&lmtimes, 0);
	return;
    }
    Dir_InitCur(cdname);

    dotLast = bmake_malloc(sizeof(Path));
    dotLast->refCount = 1;
    dotLast->hits = 0;
    dotLast->name = bmake_strdup(".DOTLAST");
    Hash_InitTable(&dotLast->files, -1);
}