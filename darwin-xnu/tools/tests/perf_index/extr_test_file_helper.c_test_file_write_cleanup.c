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
typedef  int /*<<< orphan*/  filepath ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int PERFINDEX_SUCCESS ; 
 int /*<<< orphan*/  VERIFY (int,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int unlink (char*) ; 

int test_file_write_cleanup(char* path, int num_threads, long long length) {
    int i;
    char filepath[MAXPATHLEN];
    int retval;

    for(i=0; i<num_threads; i++) {
        snprintf(filepath, sizeof(filepath), "%s/file_write-%d", path, i);
        retval = unlink(filepath);
        VERIFY(retval == 0, "unlink failed");
    }

    return PERFINDEX_SUCCESS;
}