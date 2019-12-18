#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* fdOpenInfoRef ;
struct TYPE_4__ {struct TYPE_4__* fds; struct TYPE_4__* threads; struct TYPE_4__* pids; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
check_free(fdOpenInfoRef info)
{
	if (info->pids != NULL) {
		free(info->pids);
	}

	if (info->threads != NULL) {
		free(info->threads);
	}

	if (info->fds != NULL) {
		free(info->fds);
	}

	free(info);

	return;
}