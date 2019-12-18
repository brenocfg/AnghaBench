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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 char* PLURAL (int) ; 
 int RRexpect ; 
 int RRtotal ; 
 int SRexpect ; 
 int SRtotal ; 
 int /*<<< orphan*/  exit_code ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* myname ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
total_conflicts(void)
{
    fprintf(stderr, "%s: ", myname);
    if (SRtotal == 1)
	fprintf(stderr, "1 shift/reduce conflict");
    else if (SRtotal > 1)
	fprintf(stderr, "%d shift/reduce conflicts", SRtotal);

    if (SRtotal && RRtotal)
	fprintf(stderr, ", ");

    if (RRtotal == 1)
	fprintf(stderr, "1 reduce/reduce conflict");
    else if (RRtotal > 1)
	fprintf(stderr, "%d reduce/reduce conflicts", RRtotal);

    fprintf(stderr, ".\n");

    if (SRexpect >= 0 && SRtotal != SRexpect)
    {
	fprintf(stderr, "%s: ", myname);
	fprintf(stderr, "expected %d shift/reduce conflict%s.\n",
		SRexpect, PLURAL(SRexpect));
	exit_code = EXIT_FAILURE;
    }
    if (RRexpect >= 0 && RRtotal != RRexpect)
    {
	fprintf(stderr, "%s: ", myname);
	fprintf(stderr, "expected %d reduce/reduce conflict%s.\n",
		RRexpect, PLURAL(RRexpect));
	exit_code = EXIT_FAILURE;
    }
}