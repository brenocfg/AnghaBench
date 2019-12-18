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
 char* DISQUE_VERSION ; 
 char* ZMALLOC_LIB ; 
 scalar_t__ atoi (int /*<<< orphan*/ ) ; 
 scalar_t__ disqueBuildId () ; 
 int /*<<< orphan*/  disqueGitDirty () ; 
 char* disqueGitSHA1 () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,int,char*,int,unsigned long long) ; 

void version(void) {
    printf("Disque server v=%s sha=%s:%d malloc=%s bits=%d build=%llx\n",
        DISQUE_VERSION,
        disqueGitSHA1(),
        atoi(disqueGitDirty()) > 0,
        ZMALLOC_LIB,
        sizeof(long) == 4 ? 32 : 64,
        (unsigned long long) disqueBuildId());
    exit(0);
}