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
struct qitem {int /*<<< orphan*/ * mailf; int /*<<< orphan*/  mailfn; int /*<<< orphan*/ * queuef; int /*<<< orphan*/  queuefn; } ;

/* Variables and functions */
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int open_locked (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

int
acquirespool(struct qitem *it)
{
	int queuefd;

	if (it->queuef == NULL) {
		queuefd = open_locked(it->queuefn, O_RDWR|O_NONBLOCK);
		if (queuefd < 0)
			goto fail;
		it->queuef = fdopen(queuefd, "r+");
		if (it->queuef == NULL)
			goto fail;
	}

	if (it->mailf == NULL) {
		it->mailf = fopen(it->mailfn, "r");
		if (it->mailf == NULL)
			goto fail;
	}

	return (0);

fail:
	if (errno == EWOULDBLOCK)
		return (1);
	syslog(LOG_INFO, "could not acquire queue file: %m");
	return (-1);
}