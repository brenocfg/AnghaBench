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
 int EditFilename (char*,char*,int /*<<< orphan*/ *,int) ; 
 int FileSelector (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static int BasicUIGetDirectoryPath(char *directory)
{
#ifdef DO_DIR
	return FileSelector(directory, TRUE, NULL, 0);
#else
	return EditFilename("Path", directory, NULL, -1);
#endif
}