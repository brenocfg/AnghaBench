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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  size_t TrEvent ;
struct TYPE_5__ {int pid; int flags; TYPE_1__* node; } ;
struct TYPE_4__ {char* name; int type; } ;
typedef  TYPE_2__ Job ;

/* Variables and functions */
 int /*<<< orphan*/ * evname ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jobTokensRunning ; 
 int /*<<< orphan*/ * trfile ; 
 int /*<<< orphan*/  trpid ; 
 int /*<<< orphan*/  trwd ; 

void
Trace_Log(TrEvent event, Job *job)
{
	struct timeval rightnow;
	
	if (trfile == NULL)
		return;

	gettimeofday(&rightnow, NULL);

	fprintf(trfile, "%lld.%06ld %d %s %d %s",
	    (long long)rightnow.tv_sec, (long)rightnow.tv_usec,
	    jobTokensRunning,
	    evname[event], trpid, trwd);
	if (job != NULL) {
		fprintf(trfile, " %s %d %x %x", job->node->name,
		    job->pid, job->flags, job->node->type);
	}
	fputc('\n', trfile);
	fflush(trfile);
}