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
struct TYPE_4__ {char* data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ StringInfoData ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_OR_REPLACE_COMMAND ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  quote_literal_cstr (char const*) ; 

char *
WrapCreateOrReplace(const char *sql)
{
	StringInfoData buf = { 0 };
	initStringInfo(&buf);
	appendStringInfo(&buf, CREATE_OR_REPLACE_COMMAND, quote_literal_cstr(sql));
	return buf.data;
}