#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_sec; } ;
struct TYPE_3__ {scalar_t__ tv_sec; } ;
struct stat {TYPE_1__ st_mtim; } ;
struct TYPE_4__ {int /*<<< orphan*/  spooldir; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPOOL_FLUSHFILE ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ config ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char*,struct stat*) ; 

int
flushqueue_since(unsigned int period)
{
        struct stat st;
	struct timeval now;
        char *flushfn = NULL;

	if (asprintf(&flushfn, "%s/%s", config.spooldir, SPOOL_FLUSHFILE) < 0)
		return (0);
	if (stat(flushfn, &st) < 0) {
		free(flushfn);
		return (0);
	}
	free(flushfn);
	flushfn = NULL;
	if (gettimeofday(&now, 0) != 0)
		return (0);

	/* Did the flush file get touched within the last period seconds? */
	if (st.st_mtim.tv_sec + (int)period >= now.tv_sec)
		return (1);
	else
		return (0);
}