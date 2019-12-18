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
struct dtc_file {char* name; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static int dtc_open_one(struct dtc_file *file,
                        const char *search,
                        const char *fname)
{
	char *fullname;

	if (search) {
		fullname = xmalloc(strlen(search) + strlen(fname) + 2);

		strcpy(fullname, search);
		strcat(fullname, "/");
		strcat(fullname, fname);
	} else {
		fullname = strdup(fname);
	}

	file->file = fopen(fullname, "r");
	if (!file->file) {
		free(fullname);
		return 0;
	}

	file->name = fullname;
	return 1;
}