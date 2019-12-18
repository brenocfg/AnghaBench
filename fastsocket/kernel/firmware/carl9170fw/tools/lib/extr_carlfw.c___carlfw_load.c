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
struct stat {int /*<<< orphan*/  st_size; } ;
struct carlfw_file {int /*<<< orphan*/  name; int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ENOMEM ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int fread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static int __carlfw_load(struct carlfw_file *file, const char *name, const char *mode)
{
	struct stat file_stat;
	FILE *fh;
	int err;

	fh = fopen(name, mode);
	if (fh == NULL)
		return errno ? -errno : -1;

	err = fstat(fileno(fh), &file_stat);
	if (err)
		return errno ? -errno : -1;

	file->len = file_stat.st_size;
	file->data = malloc(file->len);
	if (file->data == NULL)
		return -ENOMEM;

	err = fread(file->data, file->len, 1, fh);
	if (err != 1)
		return -ferror(fh);

	file->name = strdup(name);
	fclose(fh);

	if (!file->name)
		return -ENOMEM;

	return 0;
}