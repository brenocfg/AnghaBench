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
 int /*<<< orphan*/  MAXPATHLEN ; 
 int PERFINDEX_SUCCESS ; 
 int /*<<< orphan*/  VERIFY (int,char*) ; 
 int asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char const*) ; 
 int system (char*) ; 

int setup_ram_volume(const char* name, char* path) {
  char *cmd;
  int retval;
  
  retval = asprintf(&cmd, "diskutil erasevolume HFS+ '%s' `hdiutil attach -nomount ram://1500000` >/dev/null", name);
  VERIFY(retval > 0, "asprintf failed");

  retval = system(cmd);
  VERIFY(retval == 0, "diskutil command failed");

  snprintf(path, MAXPATHLEN, "/Volumes/%s", name);

  free(cmd);

  return PERFINDEX_SUCCESS;
}