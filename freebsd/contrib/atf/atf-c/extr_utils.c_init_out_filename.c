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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  atf_error_t ;
typedef  int /*<<< orphan*/  atf_dynstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  atf_dynstr_init_fmt (int /*<<< orphan*/ *,char*,int,char const*) ; 
 int /*<<< orphan*/  atf_error_format (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tc_fail (char*,char*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
init_out_filename(atf_dynstr_t *name, const pid_t pid, const char *suffix,
                  const bool in_parent)
{
    atf_error_t error;

    error = atf_dynstr_init_fmt(name, "atf_utils_fork_%d_%s.txt",
                                (int)pid, suffix);
    if (atf_is_error(error)) {
        char buffer[1024];
        atf_error_format(error, buffer, sizeof(buffer));
        if (in_parent) {
            atf_tc_fail("Failed to create output file: %s", buffer);
        } else {
            err(EXIT_FAILURE, "Failed to create output file: %s", buffer);
        }
    }
}