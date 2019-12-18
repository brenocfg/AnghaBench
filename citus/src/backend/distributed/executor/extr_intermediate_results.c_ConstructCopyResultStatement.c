#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  makeStringInfo () ; 

__attribute__((used)) static StringInfo
ConstructCopyResultStatement(const char *resultId)
{
	StringInfo command = makeStringInfo();

	appendStringInfo(command, "COPY \"%s\" FROM STDIN WITH (format result)",
					 resultId);

	return command;
}