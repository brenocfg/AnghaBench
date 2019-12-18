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
typedef  int /*<<< orphan*/  fielddef_t ;

/* Variables and functions */
 int MAX_STRINGFIELD ; 
 int /*<<< orphan*/  PC_ExpectTokenType (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StripDoubleQuotes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TT_STRING ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

int ReadString(source_t *source, fielddef_t *fd, void *p)
{
	token_t token;

	if (!PC_ExpectTokenType(source, TT_STRING, 0, &token)) return 0;
	//remove the double quotes
	StripDoubleQuotes(token.string);
	//copy the string
	strncpy((char *) p, token.string, MAX_STRINGFIELD);
	//make sure the string is closed with a zero
	((char *)p)[MAX_STRINGFIELD-1] = '\0';
	//
	return 1;
}