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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_error_format (int /*<<< orphan*/  const,char*,int) ; 
 scalar_t__ atf_error_is (int /*<<< orphan*/  const,char*) ; 
 int /*<<< orphan*/  atf_is_error (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static
void
print_error(const atf_error_t err)
{
    char buf[4096];

    PRE(atf_is_error(err));

    atf_error_format(err, buf, sizeof(buf));
    fprintf(stderr, "%s: ERROR: %s\n", progname, buf);

    if (atf_error_is(err, "usage"))
        fprintf(stderr, "%s: See atf-test-program(1) for usage details.\n",
                progname);
}