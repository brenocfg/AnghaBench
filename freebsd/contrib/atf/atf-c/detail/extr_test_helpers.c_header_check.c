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
typedef  int /*<<< orphan*/  failmsg ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tc_fail (char*,char*) ; 
 int /*<<< orphan*/  build_check_c_o (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

void
header_check(const char *hdrname)
{
    FILE *srcfile;
    char failmsg[128];

    srcfile = fopen("test.c", "w");
    ATF_REQUIRE(srcfile != NULL);
    fprintf(srcfile, "#include <%s>\n", hdrname);
    fclose(srcfile);

    snprintf(failmsg, sizeof(failmsg),
             "Header check failed; %s is not self-contained", hdrname);

    if (!build_check_c_o("test.c"))
        atf_tc_fail("%s", failmsg);
}