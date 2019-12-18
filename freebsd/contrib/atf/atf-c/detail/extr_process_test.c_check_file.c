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
typedef  enum out_type { ____Placeholder_out_type } out_type ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK (int) ; 
 int /*<<< orphan*/  UNREACHABLE ; 
 int atf_utils_grep_file (char*,char*) ; 
#define  stderr_type 129 
#define  stdout_type 128 

__attribute__((used)) static
void
check_file(const enum out_type type)
{
    switch (type) {
    case stdout_type:
        ATF_CHECK(atf_utils_grep_file("stdout: msg", "stdout"));
        ATF_CHECK(!atf_utils_grep_file("stderr: msg", "stdout"));
        break;
    case stderr_type:
        ATF_CHECK(atf_utils_grep_file("stderr: msg", "stderr"));
        ATF_CHECK(!atf_utils_grep_file("stdout: msg", "stderr"));
        break;
    default:
        UNREACHABLE;
    }
}