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
 int PERFINDEX_SUCCESS ; 
 int /*<<< orphan*/  VERIFY (int,char*) ; 
 int asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int system (char*) ; 

int cleanup_ram_volume(char* path) {
  char *cmd;
  int retval;

  retval = asprintf(&cmd, "umount -f '%s' >/dev/null", path);
  VERIFY(retval > 0, "asprintf failed");

  retval = system(cmd);
  VERIFY(retval == 0, "diskutil command failed");

  free(cmd);

  return PERFINDEX_SUCCESS;
}