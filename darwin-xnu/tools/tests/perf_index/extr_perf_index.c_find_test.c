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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  binpath ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 int MAXPATHLEN ; 
 int _NSGetExecutablePath (char*,int*) ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

int find_test(char* test_name, char* test_path) {
    char binpath[MAXPATHLEN];
    char* dirpath;
    uint32_t size = sizeof(binpath);
    int retval;

    retval = _NSGetExecutablePath(binpath, &size);
    assert(retval == 0);
    dirpath = dirname(binpath);

    snprintf(test_path, MAXPATHLEN, "%s/perfindex-%s.dylib", dirpath, test_name);
    if(access(test_path, F_OK) == 0)
        return 0;
    else
        return -1;
}