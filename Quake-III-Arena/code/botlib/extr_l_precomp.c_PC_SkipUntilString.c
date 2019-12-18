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
 scalar_t__ PC_ReadToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int PC_SkipUntilString(source_t *source, char *string)
{
	token_t token;

	while(PC_ReadToken(source, &token))
	{
		if (!strcmp(token.string, string)) return qtrue;
	} //end while
	return qfalse;
}