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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;

/* Variables and functions */
 int PATH_MAX ; 
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static int is_directory(const char *base_path, const struct dirent *dent)
{
	char path[PATH_MAX];
	struct stat st;

	sprintf(path, "%s/%s", base_path, dent->d_name);
	if (stat(path, &st))
		return 0;

	return S_ISDIR(st.st_mode);
}