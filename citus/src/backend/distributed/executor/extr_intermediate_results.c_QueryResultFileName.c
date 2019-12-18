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
struct TYPE_4__ {char* data; } ;
typedef  TYPE_1__* StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_NAME ; 
 int /*<<< orphan*/  ERROR ; 
 char* IntermediateResultsDirectory () ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 TYPE_1__* makeStringInfo () ; 

__attribute__((used)) static char *
QueryResultFileName(const char *resultId)
{
	StringInfo resultFileName = makeStringInfo();
	const char *resultDirectory = IntermediateResultsDirectory();
	char *checkChar = (char *) resultId;

	for (; *checkChar; checkChar++)
	{
		if (!((*checkChar >= 'a' && *checkChar <= 'z') ||
			  (*checkChar >= 'A' && *checkChar <= 'Z') ||
			  (*checkChar >= '0' && *checkChar <= '9') ||
			  (*checkChar == '_') || (*checkChar == '-')))
		{
			ereport(ERROR, (errcode(ERRCODE_INVALID_NAME),
							errmsg("result key \"%s\" contains invalid character",
								   resultId),
							errhint("Result keys may only contain letters, numbers, "
									"underscores and hyphens.")));
		}
	}

	appendStringInfo(resultFileName, "%s/%s.data",
					 resultDirectory, resultId);

	return resultFileName->data;
}