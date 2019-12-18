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
struct machine {char* root_dir; } ;
struct dso {int /*<<< orphan*/  data_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PATH_MAX ; 
 scalar_t__ dso__binary_type_file (struct dso*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int open_dso(struct dso *dso, struct machine *machine)
{
	char *root_dir = (char *) "";
	char *name;
	int fd;

	name = malloc(PATH_MAX);
	if (!name)
		return -ENOMEM;

	if (machine)
		root_dir = machine->root_dir;

	if (dso__binary_type_file(dso, dso->data_type,
				  root_dir, name, PATH_MAX)) {
		free(name);
		return -EINVAL;
	}

	fd = open(name, O_RDONLY);
	free(name);
	return fd;
}