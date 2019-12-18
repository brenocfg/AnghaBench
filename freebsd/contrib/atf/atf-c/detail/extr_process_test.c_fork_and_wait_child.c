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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  UNREACHABLE ; 
 int fork () ; 
 scalar_t__ waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int
fork_and_wait_child(void (*child_func)(void))
{
    pid_t pid;
    int status;

    pid = fork();
    ATF_REQUIRE(pid != -1);
    if (pid == 0) {
        status = 0; /* Silence compiler warnings */
        child_func();
        UNREACHABLE;
    } else {
        ATF_REQUIRE(waitpid(pid, &status, 0) != 0);
    }

    return status;
}