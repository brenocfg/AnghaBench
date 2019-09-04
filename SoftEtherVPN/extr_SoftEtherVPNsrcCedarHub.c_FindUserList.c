#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct TYPE_6__ {int /*<<< orphan*/  Filename; } ;
typedef  TYPE_1__ USERLIST ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 TYPE_1__* Search (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

USERLIST *FindUserList(LIST *o, char *filename)
{
	USERLIST t, *u;
	// Validate arguments
	if (o == NULL || filename == NULL)
	{
		return NULL;
	}

	Zero(&t, sizeof(t));

	StrCpy(t.Filename, sizeof(t.Filename), filename);

	u = Search(o, &t);

	return u;
}