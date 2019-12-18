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
 int EXIT_SUCCESS ; 
 int atf_utils_fork () ; 
 int /*<<< orphan*/  atf_utils_wait (int const,int const,char const*,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
fork_and_wait(const int exitstatus, const char* expout, const char* experr)
{
    const pid_t pid = atf_utils_fork();
    ATF_REQUIRE(pid != -1);
    if (pid == 0) {
        fprintf(stdout, "Some output\n");
        fprintf(stderr, "Some error\n");
        exit(123);
    }
    atf_utils_wait(pid, exitstatus, expout, experr);
    exit(EXIT_SUCCESS);
}