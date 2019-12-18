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
struct dirent {scalar_t__ d_type; char* d_name; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ realloc (char**,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char const*) ; 

void listdir(const char *name, char ***files, int *num_files)
{
	DIR *dir;
	struct dirent *entry;
	int cnt;

	if (!(dir = opendir(name)))
		return;

	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_DIR) {
			char path[1024];
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
			listdir(path, files, num_files);
		} else {
			cnt = *num_files;
			*files = (char **)realloc(*files, sizeof(char *) * (cnt + 1));
			(*files)[cnt] = (char *)malloc(sizeof(char) * ( strlen(name) + 1 + strlen(entry->d_name) + 10));
			sprintf((*files)[cnt], "%s/%s", name, entry->d_name);
			cnt ++;
			*num_files = cnt;
		}
	}

	closedir(dir);
}