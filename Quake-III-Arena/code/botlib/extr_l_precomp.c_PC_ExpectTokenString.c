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
struct TYPE_3__ {int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  source_t ;

/* Variables and functions */
 int /*<<< orphan*/  PC_ReadToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  SourceError (int /*<<< orphan*/ *,char*,char*,...) ; 
 int qfalse ; 
 int qtrue ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int PC_ExpectTokenString(source_t *source, char *string)
{
	token_t token;

	if (!PC_ReadToken(source, &token))
	{
		SourceError(source, "couldn't find expected %s", string);
		return qfalse;
	} //end if

	if (strcmp(token.string, string))
	{
		SourceError(source, "expected %s, found %s", string, token.string);
		return qfalse;
	} //end if
	return qtrue;
}