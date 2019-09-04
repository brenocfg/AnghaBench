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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* fdOpenInfoRef ;
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  match_stat; scalar_t__ fds_size; scalar_t__ fds_count; int /*<<< orphan*/ * fds; scalar_t__ thr_size; scalar_t__ thr_count; int /*<<< orphan*/ * threads; scalar_t__ pids_size; scalar_t__ pids_count; int /*<<< orphan*/ * pids; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int stat (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static fdOpenInfoRef
check_init(const char *path, uint32_t flags)
{
	fdOpenInfoRef	info;
	int		status;

	info = malloc(sizeof(*info));
	if (!info)
		return NULL;

	info->pids		= NULL;
	info->pids_count	= 0;
	info->pids_size		= 0;

	info->threads		= NULL;
	info->thr_count		= 0;
	info->thr_size		= 0;

	info->fds		= NULL;
	info->fds_count		= 0;
	info->fds_size		= 0;

	status = stat(path, &info->match_stat);
	if (status == -1) {
		goto fail;
	}

	info->flags		= flags;

	return info;

    fail :

	free(info);
	return NULL;
}