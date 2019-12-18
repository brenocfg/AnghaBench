#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int outPipe; int inPipe; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  JobDoOutput (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  clearfd (TYPE_1__*) ; 
 int /*<<< orphan*/  close (int) ; 

__attribute__((used)) static void
JobClose(Job *job)
{
    clearfd(job);
    (void)close(job->outPipe);
    job->outPipe = -1;

    JobDoOutput(job, TRUE);
    (void)close(job->inPipe);
    job->inPipe = -1;
}