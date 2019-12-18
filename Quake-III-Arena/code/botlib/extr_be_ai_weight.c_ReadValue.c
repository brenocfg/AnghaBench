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
struct TYPE_4__ {scalar_t__ type; float floatvalue; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  source_t ;

/* Variables and functions */
 int /*<<< orphan*/  PC_ExpectAnyToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PC_ExpectTokenType (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SourceError (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SourceWarning (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ TT_NUMBER ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int ReadValue(source_t *source, float *value)
{
	token_t token;

	if (!PC_ExpectAnyToken(source, &token)) return qfalse;
	if (!strcmp(token.string, "-"))
	{
		SourceWarning(source, "negative value set to zero\n");
		if (!PC_ExpectTokenType(source, TT_NUMBER, 0, &token)) return qfalse;
	} //end if
	if (token.type != TT_NUMBER)
	{
		SourceError(source, "invalid return value %s\n", token.string);
		return qfalse;
	} //end if
	*value = token.floatvalue;
	return qtrue;
}