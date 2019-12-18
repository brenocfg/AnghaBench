#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dirent {scalar_t__ d_type; scalar_t__ d_name; } ;
typedef  int /*<<< orphan*/  mfilters ;
typedef  int /*<<< orphan*/  buff ;
struct TYPE_2__ {char const** hwfilters; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_LNK ; 
 scalar_t__ DT_REG ; 
 char** calloc (int,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 TYPE_1__ plat_target ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewinddir (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 char* strdup (char*) ; 
 size_t strlen (scalar_t__) ; 
 int /*<<< orphan*/  strncpy (char*,scalar_t__,size_t) ; 

__attribute__((used)) static void scan_for_filters(void)
{
	struct dirent *ent;
	int i, count = 0;
	const char **mfilters;
	char buff[64];
	DIR *dir;

	dir = opendir("/etc/pandora/conf/dss_fir");
	if (dir == NULL) {
		perror("filter opendir");
		return;
	}

	while (1) {
		errno = 0;
		ent = readdir(dir);
		if (ent == NULL) {
			if (errno != 0)
				perror("readdir");
			break;
		}

		if (ent->d_type != DT_REG && ent->d_type != DT_LNK)
			continue;

		count++;
	}

	if (count == 0)
		return;

	mfilters = calloc(count + 1, sizeof(mfilters[0]));
	if (mfilters == NULL)
		return;

	rewinddir(dir);
	for (i = 0; (ent = readdir(dir)); ) {
		size_t len;

		if (ent->d_type != DT_REG && ent->d_type != DT_LNK)
			continue;

		len = strlen(ent->d_name);

		// skip pre-HF5 extra files
		if (len >= 3 && strcmp(ent->d_name + len - 3, "_v3") == 0)
			continue;
		if (len >= 3 && strcmp(ent->d_name + len - 3, "_v5") == 0)
			continue;

		// have to cut "_up_h" for pre-HF5
		if (len > 5 && strcmp(ent->d_name + len - 5, "_up_h") == 0)
			len -= 5;

		if (len > sizeof(buff) - 1)
			continue;

		strncpy(buff, ent->d_name, len);
		buff[len] = 0;
		mfilters[i] = strdup(buff);
		if (mfilters[i] != NULL)
			i++;
	}
	closedir(dir);

	plat_target.hwfilters = mfilters;
}