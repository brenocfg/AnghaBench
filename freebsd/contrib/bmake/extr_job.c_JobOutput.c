#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int noPLen; scalar_t__ noPrint; } ;
struct TYPE_4__ {scalar_t__ node; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE (int /*<<< orphan*/ ,scalar_t__) ; 
 char* Str_FindSubstring (char*,scalar_t__) ; 
 int /*<<< orphan*/  beSilent ; 
 TYPE_2__* commandShell ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ lastNode ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static char *
JobOutput(Job *job, char *cp, char *endp, int msg)
{
    char *ecp;

    if (commandShell->noPrint) {
	ecp = Str_FindSubstring(cp, commandShell->noPrint);
	while (ecp != NULL) {
	    if (cp != ecp) {
		*ecp = '\0';
		if (!beSilent && msg && job->node != lastNode) {
		    MESSAGE(stdout, job->node);
		    lastNode = job->node;
		}
		/*
		 * The only way there wouldn't be a newline after
		 * this line is if it were the last in the buffer.
		 * however, since the non-printable comes after it,
		 * there must be a newline, so we don't print one.
		 */
		(void)fprintf(stdout, "%s", cp);
		(void)fflush(stdout);
	    }
	    cp = ecp + commandShell->noPLen;
	    if (cp != endp) {
		/*
		 * Still more to print, look again after skipping
		 * the whitespace following the non-printable
		 * command....
		 */
		cp++;
		while (*cp == ' ' || *cp == '\t' || *cp == '\n') {
		    cp++;
		}
		ecp = Str_FindSubstring(cp, commandShell->noPrint);
	    } else {
		return cp;
	    }
	}
    }
    return cp;
}