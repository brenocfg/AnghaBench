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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  dialog_msgbox (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* install_partition ; 
 scalar_t__ my_system (char*,char const*) ; 
 char const* null ; 

__attribute__((used)) static void
extract_packages(const char *source_path)
{
#ifndef	DEBUG_THIS
    FILE *f;
#endif

    if (my_system("mkdir -p /install/var/installed/packages %s", null))
	return;
    if (my_system("cd /install; for i in /source%s/*.tgz; do "
		  "tar xzplvvkf $i >> var/installed/packages/base "
		  "2>>var/installed/packages/ERROR; done", source_path))
	return;
#ifndef	DEBUG_THIS
    if ((f = fopen("/install/etc/fstab", "w")) == NULL) {
	/* i = */ dialog_msgbox("Error", "Cannot write /etc/fstab",
				12, 40, 1);
	return;
    }
    fprintf(f, "%s / ext2 defaults 1 1\n", install_partition);
    fprintf(f, "none /proc proc defaults 0 2\n");
    /* XXX write swap-partitions */
    fclose(f);
#endif
}