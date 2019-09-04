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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  S_IRWXG ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 scalar_t__ mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 

int main(int argc, char** argv) {
  if (mkdir("/tmp", S_IRWXG) != 0 && errno != EEXIST) {
    printf("Unable to create dir '/tmp'\n");
    return -1;
  }

  if (mkdir("/tmp/1", S_IRWXG) != 0 && errno != EEXIST) {
    printf("Unable to create dir '/tmp/1'\n");
    return -1;
  }

  if (mkdir("/tmp/1/", S_IRWXG) != 0 && errno != EEXIST) {
    printf("Unable to create dir '/tmp/1/'\n");
    return -1;
  }

  DIR *dir = opendir("/tmp");

  if (!dir) {
    printf("Unable to open dir '/tmp'\n");
    return -2;
  }

  struct dirent *dirent;

  while ((dirent = readdir(dir)) != 0) {
    printf("Found '%s'\n", dirent->d_name);

    if (strlen(dirent->d_name) == 0) {
      printf("Found empty path!\n");
      return -3;
    }
  }

  closedir(dir);

  printf("success\n"); 

#ifdef REPORT_RESULT
  REPORT_RESULT(0);
#endif
  return 0;
}