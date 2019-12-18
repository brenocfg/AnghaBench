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
struct dirent {scalar_t__ d_type; int /*<<< orphan*/ * d_name; } ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 char** filter_exts_internal ; 
 scalar_t__ strcasecmp (char const*,char const*) ; 
 char* strrchr (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static int scandir_filter(const struct dirent *ent)
{
	const char **filter = filter_exts_internal;
	const char *ext;
	int i;

	if (ent == NULL || ent->d_name == NULL)
		return 0;

	if (ent->d_type == DT_DIR)
		return 1;

	ext = strrchr(ent->d_name, '.');
	if (ext == NULL)
		return 0;

	ext++;
	for (i = 0; filter[i] != NULL; i++)
		if (strcasecmp(ext, filter[i]) == 0)
			return 1;

	return 0;
}