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
struct TYPE_4__ {char* val; int /*<<< orphan*/ * keyword; } ;
typedef  TYPE_1__ PQconninfoOption ;

/* Variables and functions */
 int /*<<< orphan*/  AddConnParam (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  PQconninfoFree (TYPE_1__*) ; 
 TYPE_1__* PQconninfoParse (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetConnParams () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static void
NodeConninfoGucAssignHook(const char *newval, void *extra)
{
	PQconninfoOption *optionArray = NULL;
	PQconninfoOption *option = NULL;

	if (newval == NULL)
	{
		newval = "";
	}

	optionArray = PQconninfoParse(newval, NULL);
	if (optionArray == NULL)
	{
		ereport(FATAL, (errmsg("cannot parse node_conninfo value"),
						errdetail("The GUC check hook should prevent "
								  "all malformed values.")));
	}

	ResetConnParams();

	for (option = optionArray; option->keyword != NULL; option++)
	{
		if (option->val == NULL || option->val[0] == '\0')
		{
			continue;
		}

		AddConnParam(option->keyword, option->val);
	}

	PQconninfoFree(optionArray);
}