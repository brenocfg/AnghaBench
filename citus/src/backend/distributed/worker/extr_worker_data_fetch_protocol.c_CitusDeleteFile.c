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

/* Variables and functions */
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int unlink (char const*) ; 

__attribute__((used)) static void
CitusDeleteFile(const char *filename)
{
	int deleted = unlink(filename);
	if (deleted != 0)
	{
		ereport(WARNING, (errcode_for_file_access(),
						  errmsg("could not delete file \"%s\": %m", filename)));
	}
}