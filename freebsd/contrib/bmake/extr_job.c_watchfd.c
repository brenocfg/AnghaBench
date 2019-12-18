#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
struct TYPE_5__ {TYPE_4__* inPollfd; int /*<<< orphan*/  inPipe; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  Punt (char*) ; 
 TYPE_4__* fds ; 
 TYPE_1__** jobfds ; 
 size_t nfds ; 

__attribute__((used)) static void
watchfd(Job *job)
{
    if (job->inPollfd != NULL)
	Punt("Watching watched job");

    fds[nfds].fd = job->inPipe;
    fds[nfds].events = POLLIN;
    jobfds[nfds] = job;
    job->inPollfd = &fds[nfds];
    nfds++;
}