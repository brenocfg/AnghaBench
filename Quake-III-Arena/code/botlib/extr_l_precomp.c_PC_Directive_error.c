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
 int /*<<< orphan*/  PC_ReadSourceToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  SourceError (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int qfalse ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int PC_Directive_error(source_t *source)
{
	token_t token;

	strcpy(token.string, "");
	PC_ReadSourceToken(source, &token);
	SourceError(source, "#error directive: %s", token.string);
	return qfalse;
}