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
typedef  int /*<<< orphan*/  t ;
struct TYPE_4__ {int /*<<< orphan*/  ServerName; int /*<<< orphan*/  Path; } ;
typedef  TYPE_1__ LOG_FILE ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/ * Search (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

bool CheckLogFileNameFromEnumList(LIST *o, char *name, char *server_name)
{
	LOG_FILE t;
	// Validate arguments
	if (o == NULL || name == NULL || server_name == NULL)
	{
		return false;
	}

	Zero(&t, sizeof(t));
	StrCpy(t.Path, sizeof(t.Path), name);
	StrCpy(t.ServerName, sizeof(t.ServerName), server_name);

	if (Search(o, &t) == NULL)
	{
		return false;
	}

	return true;
}